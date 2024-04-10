#pragma once
class global
{
public:
	// deltaTime in seconds
	static float deltaTime;

	// frame per second
	static int FPS;

	// How much the mouse has moved
	static glm::vec2 mouseOffset;

	// Current position of the mouse
	static glm::vec2 mousePos;

	static FLOAT clearColor[4];

	static float mouseSensitivity;

	static void UpdateGlobalValues();	

	static void UpdateMouseOffset(float x, float y, float xOffset, float yOffset);

private:
	static double lastFrameTime;

	// The time when FPS was last update
	static double lastFPSTime;
	static int frameCount;
};

