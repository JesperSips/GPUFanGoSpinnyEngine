#include "pch.h"
#include "GlobalValues.h"

// Define global variables

float global::deltaTime = 0.0f;
int global::FPS = 0;

double global::lastFrameTime = glfwGetTime();
double global::lastFPSTime = glfwGetTime();
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
