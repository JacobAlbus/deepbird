#include "Window.h"

#include "Helpers.h"

namespace GameEngine {

	Window::Window() {

	}

	Window::~Window() {
		SDL_DestroyWindow(_sdl_window);
	}

	int Window::Create(const std::string& window_name, int screen_width,
		int screen_height, unsigned int current_flags) {
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (current_flags & WindowFlags::INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (current_flags & WindowFlags::FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (current_flags & WindowFlags::BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_sdl_window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL);
		if (_sdl_window == nullptr) {
			Helpers::FatalError("Window could not be initialized properly!");
		}

		_sdl_surface = SDL_GetWindowSurface(_sdl_window);
		if (_sdl_window == nullptr) {
			Helpers::FatalError("Window surface could not be initialized properly!");
		}

		SDL_GLContext gl_context = SDL_GL_CreateContext(_sdl_window);
		if (gl_context == nullptr) {
			Helpers::FatalError("GL context could not be initialized properly!");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK) {
			Helpers::FatalError("Glew could not be initialzed properly!");
		}

		std::printf("*** OpenGL VErsion: %s ***\n", glGetString(GL_VERSION));

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		// Set VSync
		SDL_GL_SetSwapInterval(1);

		// Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffer() {
		SDL_GL_SwapWindow(_sdl_window);
	}

}