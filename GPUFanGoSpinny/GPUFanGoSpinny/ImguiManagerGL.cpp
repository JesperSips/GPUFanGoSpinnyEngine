#include "pch.h"

#include "RendererGL.h"

#include "imgui.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "ImguiManager.h"

static RendererGL* rendererPtr = nullptr;
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
	RendererGL& rendererCast = dynamic_cast<RendererGL&>(p_ref);
	rendererPtr = &rendererCast;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();	
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(&p_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	windowPtr = &p_window;
}

void ImguiManager::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiManager::Update(glm::vec4& p_clearColor)
{
	// Create frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Define window
	ImGui::Begin("Imgui");
	ImGui::Text("Press P to control camera");
	ImGui::Text("Press O to control mouse");
	ImGui::ColorEdit4("Clear Color", &p_clearColor.r);
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
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
