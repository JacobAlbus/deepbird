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
	FlappyBird(bool is_ai_controlled);
	~FlappyBird();

	void Run();

private:

	void AddDeadPlayerText(size_t spritesheet_index, float text_size);

	void AddOpeningScreenText(size_t spritesheet_index, float text_size);

	void UpdateTextBoxes();

	void AddScoreText(size_t spritesheet_index, float text_size, size_t score);

	void AddFrameCountText(size_t spritesheet_index, float text_size, size_t frame_count);

	void InitSystems();

	void InitShaders();

	void GameLoop();

	void DrawGame();

	void DrawSprites();

	void PrintInitInfo() const;

	GameEngine::Window _window;

	const bool _IS_AI_CONTROLLED;

	GameStateManager _game_state_manager;
	GameEngine::TextManager _text_manager;

	const GameEngine::Sprite _BACKGROUND;
	GameEngine::GLSLProgram _color_program;
	GameEngine::SpriteBatch _sprite_batch;
	GameEngine::FPSLimiter _fps_limiter;
};


