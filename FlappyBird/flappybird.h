#pragma once

#include <GameEngine/Sprite.h>
#include <GameEngine/GLSLProgram.h>
#include <GameEngine/GLTexture.h>
#include <GameEngine/Window.h>
#include <GameEngine/SpriteBatch.h>
#include <GameEngine/Timing.h>
#include <GameEngine/TextManager.h>

#include <FlappyBird/GameStateManager.h>

#include <SDL/SDL.h>
#include <vector>
#include <GL/glew.h>

class FlappyBird {

public:
	FlappyBird(int screen_width, int screen_height);
	~FlappyBird();

	void Run();

private:

	void AddDeadPlayerText(size_t spritesheet_index, float text_size);

	void AddOpeningScreenText(size_t spritesheet_index, float text_size);

	void UpdateTextBoxes(GameState prev_game_state);

	void AddScoreText(size_t spritesheet_index, float text_size, size_t score);

	void InitSystems();

	void InitShaders();

	void GameLoop();

	void DrawGame();

	void DrawSprites();

	GameEngine::Window _window;

	int _screen_width;
	int _screen_height;

	GameStateManager _game_state_manager;
	GameEngine::TextManager _text_manager;

	const GameEngine::Sprite _BACKGROUND;
	GameEngine::GLSLProgram _color_program;
	GameEngine::SpriteBatch _sprite_batch;
	GameEngine::FPSLimiter _fps_limiter;
};


