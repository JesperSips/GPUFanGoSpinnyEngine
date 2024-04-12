#include "pch.h"

#include "RendererDX.h"

#include "imgui.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_dx12.h>

#include "ImguiManager.h"

static RendererDX* rendererPtr = nullptr;
static GLFWwindow* windowPtr = nullptr;

ImguiManager::ImguiManager()
{
}

ImguiManager::~ImguiManager()
{
}

void ImguiManager::Initialize(GLFWwindow& p_window, Renderer& p_ref)
{
	// Cast the renderer to the DX12 renderer and store it as a static global variable
	RendererDX& rendererCast = dynamic_cast<RendererDX&>(p_ref);
	rendererPtr = &rendererCast;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOther(&p_window, true);
	ImGui_ImplDX12_Init(rendererPtr->g_Device.Get(), 
		rendererPtr->g_NumFrames, 
		DXGI_FORMAT_R8G8B8A8_UNORM, 
		rendererPtr->g_RTVDescriptorHeap.Get(),
		rendererPtr->g_RTVDescriptorHeap.Get()->GetCPUDescriptorHandleForHeapStart(),
		rendererPtr->g_RTVDescriptorHeap.Get()->GetGPUDescriptorHandleForHeapStart()
	);
	
	windowPtr = &p_window;
}

void ImguiManager::Terminate()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiManager::Update(glm::vec4& p_clearColor)
{
	// Create frame
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Define window
	ImGui::Begin("Imgui");
	ImGui::Text("Press P to control camera");
	ImGui::Text("Press O to control mouse");
	ImGui::Text("Mouse Position X: %.3f Y: %.1f", global::mousePos.x, global::mousePos.y);
	ImGui::Text("%i FPS", global::FPS);
	if (ImGui::Button("Close"))
		glfwSetWindowShouldClose(windowPtr, true);
	ImGui::End();
}

void ImguiManager::Render()
{
	// Render window
	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), rendererPtr->g_CommandList.Get());
}
