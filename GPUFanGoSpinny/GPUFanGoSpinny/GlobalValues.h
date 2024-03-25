#pragma once
class global
{
public:
	// deltaTime in seconds
	static float deltaTime;

	// frame per second
	static int FPS;

	static void UpdateGlobalValues();	
private:
	static double lastFrameTime;

	// The time when FPS was last update
	static double lastFPSTime;
	static int frameCount;
};

