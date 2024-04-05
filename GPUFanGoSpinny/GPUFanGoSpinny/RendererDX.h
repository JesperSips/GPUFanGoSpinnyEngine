#pragma once
#include "Renderer.h"
using namespace Microsoft::WRL;

class RendererDX:
	public Renderer
{
public:
	RendererDX();
	~RendererDX();

	void Initialize(HINSTANCE p_hInstance, int p_width, int p_height);

	void Update();
	void Terminate();

private:
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
	UINT g_RTVDescriptorSize;
	UINT g_CurrentBackBufferIndex;

	void Render();
};

