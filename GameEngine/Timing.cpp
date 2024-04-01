#include "Timing.h"

#include <iostream>

namespace GameEngine {

	FPSLimiter::FPSLimiter(Uint32 max_fps) : 
		_max_fps(max_fps),
		_current_frame(0),
		_start_ticks(0),
		_frame_count(0), 
		_frame_time_running_sum(0) {

	}

	void FPSLimiter::Begin() {
		_start_ticks = SDL_GetTicks();
	}

	float FPSLimiter::End() {
		float fps = CalculateFPS();
		
		static int frame_counter = 0;
		frame_counter = (frame_counter + 1) % 10;
		if (frame_counter == 0) {
			std::cout << fps << std::endl;
		}

		// limit fps to _max_fps
		Uint32 frame_ticks = SDL_GetTicks() - _start_ticks;
		Uint32 desired_ticks = 1000 / _max_fps;
		if (desired_ticks > frame_ticks) {
			SDL_Delay(desired_ticks - frame_ticks);
		}

		return fps;
	}

	float FPSLimiter::CalculateFPS() {
		_frame_time_running_sum -= _frame_times[_current_frame];

		_current_frame = (_current_frame + 1) % NUM_SAMPLES;

		Uint32 current_ticks = SDL_GetTicks();
		_frame_times[_current_frame] = current_ticks - _start_ticks;

		_frame_time_running_sum += _frame_times[_current_frame];

		float frame_time_average = (float) _frame_time_running_sum / NUM_SAMPLES;
		float fps = 1000.0f / frame_time_average;
		return fps;
	}

	Timer::Timer() {
		StartTime();
	}

	void Timer::StartTime() {
		_start_ticks = SDL_GetTicks();
	}

	float Timer::GetElapsedTime() const {
		return (SDL_GetTicks() - _start_ticks) / 1000.0f;
	}
}