#pragma once
class global
{
public:
	// deltaTime in seconds
	static float deltaTime;

	// frame per second
	static float FPS;

	static void UpdateGlobalValues();	
private:
	static float lastFrameTime;

	// The time when FPS was last update
	static float lastFPSTime;
	static int frameCount;
};

