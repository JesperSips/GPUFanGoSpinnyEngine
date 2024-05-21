#include "pch.h"
#include "GlobalValues.h"

// Initialize global variables

float global::deltaTime = 0.0f;
int global::FPS = 0;

glm::vec2 global::mouseOffset = glm::vec2(0);
glm::vec2 global::mousePos = glm::vec2(0);
float global::mouseSensitivity = 0.05f;

double global::lastFrameTime = glfwGetTime();
double global::lastFPSTime = glfwGetTime();
int global::frameCount = 0;

int global::clientHeight = 0;
int global::clientWidth = 0;

// This gets called in the main Update loop in Engine.cpp
void global::UpdateGlobalValues()
{
	// Reset mouse offset to 0 at the start of each frame
	mouseOffset.x = 0.f;
	mouseOffset.y = 0.f;

	double currentFrameTime = glfwGetTime();
	deltaTime = static_cast<float>(currentFrameTime - lastFrameTime);
	lastFrameTime = currentFrameTime;

	frameCount++;
	if (currentFrameTime - lastFPSTime >= 1.0) {
		FPS = frameCount;
		frameCount = 0;
		lastFPSTime = currentFrameTime;
	}
}

// This gets called in the MouseCallback function in Window.cpp
void global::UpdateMouseOffset(float x, float y, float xOffset, float yOffset)
{
	mousePos.x = x;
	mousePos.y = y;
	mouseOffset.x = xOffset;
	mouseOffset.y = yOffset;
}

void global::SetWidthAndHeight(int width, int height)
{
	clientWidth = width;
	clientHeight = height;
}
