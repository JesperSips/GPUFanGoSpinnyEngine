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

	static float mouseSensitivity;

	static void UpdateGlobalValues();	

	static void UpdateMouseOffset(float x, float y, float xOffset, float yOffset);

	inline static int GetClientWidth() { return clientWidth; }
	inline static int GetClientHeight() { return clientHeight; }

	static void SetWidthAndHeight(int width, int height);

private:
	static double lastFrameTime;

	// The time when FPS was last update
	static double lastFPSTime;
	static int frameCount;

	static int clientWidth;
	static int clientHeight;

};

