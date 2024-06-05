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




	// Placeholder mesh objects, these will be moved to their appropiate files later
	const UINT64 vbByteSize = 8 * sizeof(Vertex);
	ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
	ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;

	const UINT ibByteSize = 36 * sizeof(uint16_t);
	ComPtr<ID3D12Resource> IndexBufferGPU = nullptr;
	ComPtr<ID3D12Resource> IndexBufferUploader = nullptr;

	// Cube vertices with no texcoords, placeholder
	// Will use mesh class later if i can be bother to continue working on this
	Vertex ph_vertices[8] =
	{
		// positions,       // rgb color      
		 0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.5f, 0.6f, 0.2f, 1.0f,// bottom right
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,// bottom left
		-0.5f,  0.5f, 0.5f, 0.4f, 1.0f, 0.6f,// top left 
		// positions,       // rgb color      
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top right
		 0.5f, -0.5f, -0.5f, 0.6f, 0.2f, 1.0f,// bottom right
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,// bottom left
		-0.5f,  0.5f, -0.5f, 0.4f, 1.0f, 0.6f// top left 

	};

	uint16_t ph_indices[36] =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};
};

