// Most code in here is from Learning DirectX12 
// By Jeremiah van Oosten https://www.3dgep.com/learning-directx-12-1/#DirectX_12_Demo 
#pragma once
#include "Renderer.h"
using namespace Microsoft::WRL;

class ImguiManager;
class RendererDX:
	public Renderer
{
public:
	RendererDX();
	~RendererDX();

	void Initialize(int p_width, int p_height);

	void Update();
	void Terminate();

	void Resize(int p_width, int p_height);

private:
	friend class ImguiManager;

	// The number of swap chain back buffers.
	static const uint8_t g_NumFrames = 3;

	// Use WARP adapter
	bool g_UseWarp = false;

	// DirectX 12 Objects
	ComPtr<ID3D12Device2> g_Device;
	ComPtr<ID3D12CommandQueue> g_CommandQueue;
	ComPtr<IDXGISwapChain4> g_SwapChain;
	ComPtr<ID3D12Resource> g_BackBuffers[g_NumFrames];
	ComPtr<ID3D12GraphicsCommandList> g_CommandList;
	ComPtr<ID3D12CommandAllocator> g_CommandAllocators[g_NumFrames];
	ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap;
	ComPtr<ID3D12DescriptorHeap> g_DSVDescriptorHeap;
	UINT g_RTVDescriptorSize;
	UINT g_DSVDescriptorSize;
	UINT g_CurrentBackBufferIndex;

	D3D12_VIEWPORT m_viewPort;
	D3D12_RECT m_rect;

	// Synchronization objects
	ComPtr<ID3D12Fence> g_Fence;
	uint64_t g_FenceValue = 0;
	uint64_t g_FrameFenceValues[g_NumFrames] = {};
	HANDLE g_FenceEvent;
	
	// Object creation functions
	ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);
	ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter4> adapter);
	ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	ComPtr<IDXGISwapChain4> CreateSwapChain(HWND hWnd, ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount);
	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors);
	void UpdateRenderTargetViews(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap);
	void UpdateDepthStencilView(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap);
	ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	ComPtr<ID3D12GraphicsCommandList> CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type);
	ComPtr<ID3D12Fence> CreateFence(ComPtr<ID3D12Device2> device);
	HANDLE CreateEventHandle();

	// Buffers
	ComPtr<ID3D12Resource> m_depthStencilBuffer;

	uint64_t Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue);
	void WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent, std::chrono::milliseconds duration = std::chrono::milliseconds::max());
	void Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent);

	void Render();

	// From DXSampleHelper.h 
	// Source: https://github.com/Microsoft/DirectX-Graphics-Samples
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw std::exception();
		}
	}
};

