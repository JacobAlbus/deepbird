#include "flappybird.h"
#include  <iostream>

#include <GameEngine/Helpers.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::stringstream ss;
		ss << "Expected 3 arguments, received " << argc;
		GameEngine::Helpers::FatalError(ss.str());
	}

	bool is_ai_controlled;
	std::istringstream(argv[1]) >> std::boolalpha >> is_ai_controlled;

	bool is_display_screen;
	std::istringstream(argv[2]) >> std::boolalpha >> is_display_screen;

	FlappyBird game(is_ai_controlled, is_display_screen);
	game.Run();
	return 0;
}