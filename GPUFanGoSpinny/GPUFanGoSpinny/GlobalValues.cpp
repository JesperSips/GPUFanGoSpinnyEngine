#include "pch.h"
#include "GlobalValues.h"

// Define global variables

float global::deltaTime = 0.0f;
float global::FPS = 0.0f;

float global::lastFrameTime = glfwGetTime();
float global::lastFPSTime = glfwGetTime();
int global::frameCount = 0;

void global::UpdateGlobalValues()
{
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
