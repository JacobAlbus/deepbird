#include "flappybird.h"
#include  <iostream>

int main(int argc, char** argv) {
	FlappyBird game(640, 960);
	game.Run();
	return 0;
}