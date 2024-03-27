#include "pch.h"

#include "imgui.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "ImguiManager.h"

static GLFWwindow* window = nullptr;

ImguiManager::ImguiManager()
{
}

ImguiManager::~ImguiManager()
{
}

void ImguiManager::Initialize(GLFWwindow* p_window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();	
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	window = p_window;
}

void ImguiManager::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiManager::Update()
{
	// Create frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Define window
	static int testCounter = 0;

	ImGui::Begin("Imgui");
	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		testCounter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", testCounter);
	if (ImGui::Button("Close"))
		glfwSetWindowShouldClose(window, true);

	ImGui::Text("%i FPS", global::FPS);
	ImGui::End();
}

void ImguiManager::Render()
{
	// Render window
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}