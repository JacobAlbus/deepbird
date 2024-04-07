#include "flappybird.h"
#include  <iostream>

#include <GameEngine/Helpers.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::stringstream ss;
		ss << "Expected 2 arguments, received " << argc;
		GameEngine::Helpers::FatalError(ss.str());
	}

	bool is_ai_controlled;
	std::istringstream(argv[1]) >> std::boolalpha >> is_ai_controlled;

	FlappyBird game(is_ai_controlled);
	game.Run();
	return 0;
}