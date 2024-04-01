// GameEngine.cpp : Defines the functions for the static library.
//

#include "framework.h"
#include <SDL/SDL.h>
#include <GL/glew.h>

namespace GameEngine {

	// TODO: This is an example of a library function
	void fnGameEngine()
	{
	}

	int init() {
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}