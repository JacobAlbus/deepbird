#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace GameEngine {

	enum WindowFlags {
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window {

	public:
		Window();

		~Window();

		int Create(const std::string& window_name, int screen_width,
					int screen_height, unsigned int current_flags);

		void SwapBuffer();

		SDL_Surface* GetSurface() const { return _sdl_surface; }

		int GetHeight() const { return _screen_height; }
		int GetWidth() const { return _screen_width; }

	private:
		SDL_Window* _sdl_window;
		SDL_Surface* _sdl_surface;

		int _screen_width;
		int _screen_height;

	};

}