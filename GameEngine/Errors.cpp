#include "Errors.h"

#include <iostream>
#include <SDL/SDL.h>

void FatalError(std::string error_string) {
	std::cout << error_string << std::endl;
	std::cout << "Press any key to quit..." << std::endl;

	int temp;
	std::cin >> temp;
	SDL_Quit();
}