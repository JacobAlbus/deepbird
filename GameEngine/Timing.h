#pragma once

#include <stdint.h>
#include <SDL/SDL.h>

namespace GameEngine {

class FPSLimiter {

public:
	FPSLimiter(Uint32 max_fps);

	/*
	Initialize FPS calculation. Call before rendering/updating game state
	*/
	void Begin();

	/*
	Returns current FPS. Call After rendering/updating game state
	*/
	float End();

private:
	float CalculateFPS(); 

	void DisplayFPS() const;

	Uint32 _max_fps;
	int _current_frame;
	uint32_t _start_ticks;
	int _frame_count;
	uint32_t _frame_time_running_sum;

	static const int NUM_SAMPLES = 10;
	uint32_t _frame_times[NUM_SAMPLES];
};

class Timer {
public:

	Timer();

	void StartTime();

	// Returns elapsed time since last call of StartTime, in seconds
	float GetElapsedTime() const;

private:

	Uint32 _start_ticks;

};

}