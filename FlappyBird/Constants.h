#pragma once

#include <GameEngine/Vertex.h>
#include <GameEngine/Sprite.h>
#include "GameStateManager.h"
#include <glm/glm.hpp>
#include <string>

namespace Consts {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 960;

	const int PLAYER_WIDTH = 70;
	const int PLAYER_HEIGHT = 50;
	const glm::vec4 PLAYER_INITIAL_POSITION(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT);
	const float GRAVITY = 30;
	const float JUMP_VELOCITY = 5;

	const GameEngine::Color DEFAULT_COLOR(255, 255, 255, 255);

	const int MIN_PIPE_HEIGHT = 150;
	const float PIPE_SPEED = -3.0f;
	const int PIPE_WIDTH = 120;
	const int PIPE_DISTANCE = 300; // Vertical distance between pair of pipes
	const std::string PIPE_TEXTURE_PATH = "Textures/jimmy_jump/PNG/pipe.png";
	const std::string UPSIDE_DOWN_PIPE_TEXTURE_PATH = "Textures/jimmy_jump/PNG/upsidedown_pipe.png";
	const int PIPE_HEIGHT_RANGE = (Consts::SCREEN_HEIGHT - Consts::MIN_PIPE_HEIGHT - Consts::PIPE_DISTANCE - Consts::MIN_PIPE_HEIGHT);

	const std::string START_MESSAGE = "*!*!*";
	const std::string END_MESSAGE = "!*!*!";

	const float MESSAGE_TEXT_SIZE = 20.0f;
	const float SCORE_TEXT_SIZE = 50.0f;

	const glm::vec2 DEAD_PLAYER_TEXT_POS(0, Consts::SCREEN_HEIGHT - 100);
	const glm::vec2 OPENING_TEXT_POS(0, Consts::SCREEN_HEIGHT - 100);
	const glm::vec2 SCORE_TEXT_POS(SCREEN_WIDTH / 2, Consts::SCREEN_HEIGHT - 100);
	const glm::vec2 FRAME_COUNT_TEXT_POS(0, 0);

	const std::map<InputTypes, SDL_Keycode> INPUT_TO_KEY = {
		{InputTypes::JUMP, SDL_KeyCode::SDLK_SPACE}, {InputTypes::NOTHING, SDL_KeyCode::SDLK_0}, 
		{InputTypes::RESET, SDL_KeyCode::SDLK_q}
	};

	const std::map<char, glm::vec2> TEXT_SPRITE_SHEET_MAPPER = {
		{'A', glm::vec2(0, 8)}, {'B', glm::vec2(1, 8)}, {'C', glm::vec2(2, 8)},
		{'D', glm::vec2(3, 8)}, {'E', glm::vec2(4, 8)}, {'F', glm::vec2(5, 8)},
		{'G', glm::vec2(6, 8)}, {'H', glm::vec2(7, 8)}, {'I', glm::vec2(8, 8)},
		{'J', glm::vec2(9, 8)}, {'K', glm::vec2(0, 7)}, {'L', glm::vec2(1, 7)},
		{'M', glm::vec2(2, 7)}, {'N', glm::vec2(3, 7)}, {'O', glm::vec2(4, 7)},
		{'P', glm::vec2(5, 7)}, {'Q', glm::vec2(6, 7)}, {'R', glm::vec2(7, 7)},
		{'S', glm::vec2(8, 7)}, {'T', glm::vec2(9, 7)}, {'U', glm::vec2(0, 6)},
		{'V', glm::vec2(1, 6)}, {'W', glm::vec2(2, 6)}, {'X', glm::vec2(3, 6)},
		{'Y', glm::vec2(4, 6)}, {'Z', glm::vec2(5, 6)}, {'a', glm::vec2(6, 6)}, 
		{'b', glm::vec2(7, 6)}, {'c', glm::vec2(8, 6)}, {'d', glm::vec2(9, 6)},
		{'e', glm::vec2(0, 5)}, {'f', glm::vec2(1, 5)}, {'g', glm::vec2(2, 5)},
		{'h', glm::vec2(3, 5)}, {'i', glm::vec2(4, 5)}, {'j', glm::vec2(5, 5)},
		{'k', glm::vec2(6, 5)}, {'l', glm::vec2(7, 5)}, {'m', glm::vec2(8, 5)},
		{'n', glm::vec2(9, 5)}, {'o', glm::vec2(0, 4)}, {'p', glm::vec2(1, 4)},
		{'q', glm::vec2(2, 4)}, {'r', glm::vec2(3, 4)}, {'s', glm::vec2(4, 4)},
		{'t', glm::vec2(5, 4)}, {'u', glm::vec2(6, 4)}, {'v', glm::vec2(7, 4)},
		{'w', glm::vec2(8, 4)}, {'x', glm::vec2(9, 4)}, {'y', glm::vec2(0, 3)},
		{'z', glm::vec2(1, 3)}, {'0', glm::vec2(2, 3)}, {'1', glm::vec2(3, 3)},
		{'2', glm::vec2(4, 3)}, {'3', glm::vec2(5, 3)}, {'4', glm::vec2(6, 3)},
		{'5', glm::vec2(7, 3)}, {'6', glm::vec2(8, 3)}, {'7', glm::vec2(9, 3)},
		{'8', glm::vec2(0, 2)}, {'9', glm::vec2(1, 2)}, {'.', glm::vec2(2, 2)},
		{',', glm::vec2(3, 2)}, {';', glm::vec2(4, 2)}, {':', glm::vec2(5, 2)},
		{'?', glm::vec2(6, 2)}, {'!', glm::vec2(7, 2)}, {'-', glm::vec2(8, 2)},
		{'#', glm::vec2(9, 2)}, {'"', glm::vec2(0, 1)}, {'\'', glm::vec2(1, 1)},
		{'&', glm::vec2(2, 1)}, {'(', glm::vec2(3, 1)}, {')', glm::vec2(4, 1)},
		{'[', glm::vec2(5, 1)}, {']', glm::vec2(6, 1)},  {'\\', glm::vec2(8, 1)},
		{'/', glm::vec2(9, 1)}, {'+', glm::vec2(0, 3)}, {'=', glm::vec2(0, 4)},
		{'*', glm::vec2(0, 5)}, {'$', glm::vec2(0, 6)}, {'<', glm::vec2(0, 7)},
		{'>', glm::vec2(0, 8)}, {'%', glm::vec2(0, 9)}
	};


	const glm::vec4 BACKGROUND_POSITION(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	const std::string BACKGROUND_TEXTURE_FILE_PATH = "Textures/jimmy_jump/PNG/Backgrounds/peakpx.png";
}
