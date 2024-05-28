#include "pch.h"

#include "ImguiManager.h"
#include "Mesh.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "RendererDX.h"

RendererDX::RendererDX()
{
}

RendererDX::~RendererDX()
{
}

void RendererDX::Initialize(int p_width, int p_height)
{
#if defined(_DEBUG)
    // Always enable the debug layer before doing anything DX12 related
    // so all possible errors generated while creating DX12 objects
    // are caught by the debug layer.
    ComPtr<ID3D12Debug> debugInterface;
    ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugInterface)));
    debugInterface->EnableDebugLayer();
#endif

    // Non-DirectX12 initialization code
    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "GLFW init failed" << std::endl;
        throw;
    }

    m_window = new Window(*this, p_width, p_height, "GPU fan go spinny engine");

    // Imgui has been implemented, but crashes because I dont have a rendering pipeline yet, whoopsie
    //m_GUI = new ImguiManager();

    // The nightmare begins
    ComPtr<IDXGIAdapter4> dxgiAdapter4 = GetAdapter(g_UseWarp);

    g_Device = CreateDevice(dxgiAdapter4);

    g_CommandQueue = CreateCommandQueue(g_Device, D3D12_COMMAND_LIST_TYPE_DIRECT);

    g_SwapChain = CreateSwapChain(m_window->GetWin32Window(), g_CommandQueue, p_width, p_height, g_NumFrames);

    g_CurrentBackBufferIndex = g_SwapChain->GetCurrentBackBufferIndex();

    g_RTVDescriptorHeap = CreateDescriptorHeap(g_Device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, g_NumFrames);
    g_RTVDescriptorSize = g_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    g_DSVDescriptorHeap = CreateDescriptorHeap(g_Device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1);
    g_DSVDescriptorSize = g_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

    for (int i = 0; i < g_NumFrames; ++i)
    {
        g_CommandAllocators[i] = CreateCommandAllocator(g_Device, D3D12_COMMAND_LIST_TYPE_DIRECT);
    }
    g_CommandList = CreateCommandList(g_Device, g_CommandAllocators[g_CurrentBackBufferIndex], D3D12_COMMAND_LIST_TYPE_DIRECT);

    g_Fence = CreateFence(g_Device);
    g_FenceEvent = CreateEventHandle();

    // Initial resize to set RTV and DSV
    Resize(p_width,p_height);

    // Imgui needs DX12 objects, so initialize it after everything else
    //m_GUI->Initialize(*m_window->GetWindow(), *this);
}

void RendererDX::Update()
{
    glfwPollEvents();

    //m_GUI->Update();

    Render();
    m_window->Update();
}

void RendererDX::Terminate()
{
    // Make sure the command queue has finished all commands before closing.
    Flush(g_CommandQueue, g_Fence, g_FenceValue, g_FenceEvent);

    ::CloseHandle(g_FenceEvent);

    glfwTerminate();
}

void RendererDX::Resize(int p_width, int p_height)
{
    Flush(g_CommandQueue, g_Fence, g_FenceValue, g_FenceEvent);

    ThrowIfFailed(g_CommandList->Reset(g_CommandAllocators[g_CurrentBackBufferIndex].Get(), nullptr));

    for (int i = 0; i < g_NumFrames; ++i)
    {
        // Any references to the back buffers must be released
        // before the swap chain can be resized.
        g_BackBuffers[i].Reset();
        g_FrameFenceValues[i] = g_FrameFenceValues[g_CurrentBackBufferIndex];
    }

    m_depthStencilBuffer.Reset();

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    ThrowIfFailed(g_SwapChain->GetDesc(&swapChainDesc));
    ThrowIfFailed(g_SwapChain->ResizeBuffers(g_NumFrames, p_width, p_height, swapChainDesc.BufferDesc.Format, swapChainDesc.Flags));

    g_CurrentBackBufferIndex = g_SwapChain->GetCurrentBackBufferIndex();

    UpdateRenderTargetViews(g_Device, g_SwapChain, g_RTVDescriptorHeap);
    UpdateDepthStencilView(g_Device, g_SwapChain, g_DSVDescriptorHeap);

    m_viewPort.TopLeftX = 0.0f;
    m_viewPort.TopLeftY = 0.0f;
    m_viewPort.Width = static_cast<float>(p_width);
    m_viewPort.Height = static_cast<float>(p_height);
    m_viewPort.MinDepth = 0.0f;
    m_viewPort.MaxDepth = 1.0f;

    g_CommandList->RSSetViewports(1, &m_viewPort);

    m_rect.left = 0;
    m_rect.top = 0;
    m_rect.right = p_width / 2;
    m_rect.bottom = p_height / 2;

    g_CommandList->RSSetScissorRects(1, &m_rect);

    ThrowIfFailed(g_CommandList->Close());
    ID3D12CommandList* const commandLists[] = {
    g_CommandList.Get()
    };
    g_CommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    // Wait for resize to finish
    Flush(g_CommandQueue, g_Fence, g_FenceValue, g_FenceEvent);
}

ComPtr<IDXGIAdapter4> RendererDX::GetAdapter(bool useWarp)
{
    ComPtr<IDXGIFactory4> dxgiFactory;
    UINT createFactoryFlags = 0;
#if defined(_DEBUG)
    createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));

    ComPtr<IDXGIAdapter1> dxgiAdapter1;
    ComPtr<IDXGIAdapter4> dxgiAdapter4;

    if (useWarp)
    {
        ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&dxgiAdapter1)));
        ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
    }
    else
    {
        SIZE_T maxDedicatedVideoMemory = 0;
        for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i)
        {
            DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
            dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

            // Check to see if the adapter can create a D3D12 device without actually 
            // creating it. The adapter with the largest dedicated video memory
            // is favored.
            if ((dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
                SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(),
                    D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
                dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory)
            {
                maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
                ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
            }
        }
    }

    return dxgiAdapter4;
}

ComPtr<ID3D12Device2> RendererDX::CreateDevice(ComPtr<IDXGIAdapter4> adapter)
{
    ComPtr<ID3D12Device2> d3d12Device2;
    ThrowIfFailed(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&d3d12Device2)));

    // Enable debug messages in debug mode.
#if defined(_DEBUG)
    ComPtr<ID3D12InfoQueue> pInfoQueue;
    if (SUCCEEDED(d3d12Device2.As(&pInfoQueue)))
    {
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);
        // Suppress whole categories of messages

        // Suppress messages based on their severity level
        D3D12_MESSAGE_SEVERITY Severities[] =
        {
            D3D12_MESSAGE_SEVERITY_INFO
        };

        // Suppress individual messages by their ID
        D3D12_MESSAGE_ID DenyIds[] = {
            D3D12_MESSAGE_ID_CLEARRENDERTARGETVIEW_MISMATCHINGCLEARVALUE,   
            D3D12_MESSAGE_ID_MAP_INVALID_NULLRANGE,                         // This warning occurs when using capture frame while graphics debugging.
            D3D12_MESSAGE_ID_UNMAP_INVALID_NULLRANGE,                       // This warning occurs when using capture frame while graphics debugging.
        };

        D3D12_INFO_QUEUE_FILTER NewFilter = {};
        //NewFilter.DenyList.NumCategories = _countof(Categories);
        //NewFilter.DenyList.pCategoryList = Categories;
        NewFilter.DenyList.NumSeverities = _countof(Severities);
        NewFilter.DenyList.pSeverityList = Severities;
        NewFilter.DenyList.NumIDs = _countof(DenyIds);
        NewFilter.DenyList.pIDList = DenyIds;

        ThrowIfFailed(pInfoQueue->PushStorageFilter(&NewFilter));
    }
#endif

    return d3d12Device2;
}

ComPtr<ID3D12CommandQueue> RendererDX::CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type)
{
    ComPtr<ID3D12CommandQueue> d3d12CommandQueue;

    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = type;
    desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.NodeMask = 0;

    ThrowIfFailed(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&d3d12CommandQueue)));

    return d3d12CommandQueue;
}

ComPtr<IDXGISwapChain4> RendererDX::CreateSwapChain(HWND hWnd, ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount)
{
    ComPtr<IDXGISwapChain4> dxgiSwapChain4;
    ComPtr<IDXGIFactory4> dxgiFactory4;
    UINT createFactoryFlags = 0;
#if defined(_DEBUG)
    createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory4)));

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.Width = width;
    swapChainDesc.Height = height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.Stereo = FALSE;
    swapChainDesc.SampleDesc = { 1, 0 };
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = bufferCount;
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    // TODO: check if DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING should be included later
    swapChainDesc.Flags = 0;

    ComPtr<IDXGISwapChain1> swapChain1;
    ThrowIfFailed(dxgiFactory4->CreateSwapChainForHwnd(
        commandQueue.Get(),
        hWnd,
        &swapChainDesc,
        nullptr,
        nullptr,
        &swapChain1));

   // Disable the Alt+Enter fullscreen toggle feature. Switching to fullscreen
    // will be handled manually.
    ThrowIfFailed(dxgiFactory4->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER));

    ThrowIfFailed(swapChain1.As(&dxgiSwapChain4));

   return dxgiSwapChain4;
}

ComPtr<ID3D12DescriptorHeap> RendererDX::CreateDescriptorHeap(ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors)
{
    ComPtr<ID3D12DescriptorHeap> descriptorHeap;

    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.NumDescriptors = numDescriptors;
    desc.Type = type;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    desc.NodeMask = 0;

    ThrowIfFailed(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descriptorHeap)));

    return descriptorHeap;
}

void RendererDX::UpdateRenderTargetViews(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap)
{
    auto rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < g_NumFrames; ++i)
    {
        ComPtr<ID3D12Resource> backBuffer;
        ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));

        device->CreateRenderTargetView(backBuffer.Get(), nullptr, rtvHandle);

        g_BackBuffers[i] = backBuffer;

        rtvHandle.ptr += rtvDescriptorSize;
    }
}

void RendererDX::UpdateDepthStencilView(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap)
{
    // Describe and create the depth stencil view (DSV)
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

    D3D12_RESOURCE_DESC depthStencilDesc = {};
    depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    depthStencilDesc.Alignment = 0;
    depthStencilDesc.Width = global::GetClientWidth();
    depthStencilDesc.Height = global::GetClientHeight();
    depthStencilDesc.DepthOrArraySize = 1;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // This is the one they use in the book, might have to change later
    depthStencilDesc.SampleDesc.Count = 1; // Book uses 4 or 1 based on 4xMsaa anti-aliasing, I'll have to implement that later
    depthStencilDesc.SampleDesc.Quality = 0; // Same as above
    depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    D3D12_CLEAR_VALUE optClear = {};
    optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    optClear.DepthStencil.Depth = 1.0f;
    optClear.DepthStencil.Stencil = 0;

    D3D12_HEAP_PROPERTIES heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

    ThrowIfFailed(device->CreateCommittedResource(&heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &depthStencilDesc,
        D3D12_RESOURCE_STATE_COMMON,
        &optClear,
        IID_PPV_ARGS(m_depthStencilBuffer.GetAddressOf())));

    device->CreateDepthStencilView(m_depthStencilBuffer.Get(), &dsvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());

    // Transition the resource to be used as a depth buffer
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_depthStencilBuffer.Get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    g_CommandList->ResourceBarrier(1, &barrier);
}

ComPtr<ID3D12CommandAllocator> RendererDX::CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type)
{
    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ThrowIfFailed(device->CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)));

    return commandAllocator;
}

ComPtr<ID3D12GraphicsCommandList> RendererDX::CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type)
{
    ComPtr<ID3D12GraphicsCommandList> commandList;
    ThrowIfFailed(device->CreateCommandList(0, type, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));

    ThrowIfFailed(commandList->Close());

    return commandList;
}

ComPtr<ID3D12Fence> RendererDX::CreateFence(ComPtr<ID3D12Device2> device)
{
    ComPtr<ID3D12Fence> fence;

    ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));

    return fence;
}

HANDLE RendererDX::CreateEventHandle()
{
    HANDLE fenceEvent;

    fenceEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
    assert(fenceEvent && "Failed to create fence event.");

    return fenceEvent;
}

uint64_t RendererDX::Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue)
{
    uint64_t fenceValueForSignal = ++fenceValue;
    ThrowIfFailed(commandQueue->Signal(fence.Get(), fenceValueForSignal));

    return fenceValueForSignal;
}

void RendererDX::WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent, std::chrono::milliseconds duration)
{
    if (fence->GetCompletedValue() < fenceValue)
    {
        ThrowIfFailed(fence->SetEventOnCompletion(fenceValue, fenceEvent));
        ::WaitForSingleObject(fenceEvent, static_cast<DWORD>(duration.count()));
    }
}

void RendererDX::Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent)
{
    uint64_t fenceValueForSignal = Signal(commandQueue, fence, fenceValue);
    WaitForFenceValue(fence, fenceValueForSignal, fenceEvent);
}

void RendererDX::Render()
{
    auto commandAllocator = g_CommandAllocators[g_CurrentBackBufferIndex];
    auto backBuffer = g_BackBuffers[g_CurrentBackBufferIndex];

    commandAllocator->Reset();
    g_CommandList->Reset(commandAllocator.Get(), nullptr);

    // Clear render target
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = backBuffer.Get();
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

    g_CommandList->ResourceBarrier(1, &barrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtv;
    rtv.ptr = g_RTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart().ptr + g_CurrentBackBufferIndex * g_RTVDescriptorSize;

    FLOAT clearColor[4] = { m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a };

    g_CommandList->ClearRenderTargetView(rtv, clearColor, 0, nullptr);

    // Present
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter =D3D12_RESOURCE_STATE_PRESENT;

    g_CommandList->ResourceBarrier(1, &barrier);

    ThrowIfFailed(g_CommandList->Close());

    ID3D12CommandList* const commandLists[] = {
        g_CommandList.Get()
    };
    g_CommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    ThrowIfFailed(g_SwapChain->Present(0, 0));

    g_FrameFenceValues[g_CurrentBackBufferIndex] = Signal(g_CommandQueue, g_Fence, g_FenceValue);


    g_CurrentBackBufferIndex = g_SwapChain->GetCurrentBackBufferIndex();

    WaitForFenceValue(g_Fence, g_FrameFenceValues[g_CurrentBackBufferIndex], g_FenceEvent);
}
