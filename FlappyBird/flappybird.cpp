#include "flappybird.h"

#include <GameEngine/Helpers.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/ResourceManager.h>

#include "FlappyBird/Constants.h"

#include <string>
#include <iostream>

FlappyBird::FlappyBird(bool is_ai_controlled) : 
	_IS_AI_CONTROLLED(is_ai_controlled),
	_text_manager(),
	_game_state_manager("Textures/jimmy_jump/PNG/bird.png", 
						"Textures/jimmy_jump/PNG/pipe.png", 
						"Textures/jimmy_jump/PNG/upsidedown_pipe.png"),
	_fps_limiter(60),
	_BACKGROUND(Consts::BACKGROUND_TEXTURE_FILE_PATH, Consts::BACKGROUND_POSITION, Consts::DEFAULT_COLOR) {
}

FlappyBird::~FlappyBird() {

}

void FlappyBird::Run() {
	InitSystems();
	GameLoop();
}

void FlappyBird::GameLoop() {
	while (_game_state_manager.IsPlaying()) {
		_fps_limiter.Begin();

		_game_state_manager.UpdateCamera(_IS_AI_CONTROLLED);
		_game_state_manager.UpdateState(_IS_AI_CONTROLLED);

		UpdateTextBoxes();

		DrawGame();

		// Check if player just died

		_fps_limiter.End();
	}
}

void FlappyBird::DrawGame() {
	// Clear screen
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_color_program.Use();

	glActiveTexture(GL_TEXTURE0);
	
	// Set the texture
	GLint texture_location = _color_program.GetUniformLocation("mySampler");
	glUniform1i(texture_location, 0);

	// Set the camera matrix
	GLint matrix_location = _color_program.GetUniformLocation("orthoProjectionMatrix");
	glm::mat4 camera_matrix = _game_state_manager.GetCamera().GetCameraMatrix();
	glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &(camera_matrix[0][0]));

	// Draw Sprites
	_sprite_batch.Begin(GameEngine::GlyphSortType::TEXTURE);

	DrawSprites();

	_sprite_batch.End();

	_sprite_batch.RenderBatches();

	glBindTexture(GL_TEXTURE_2D, 0);

	_color_program.Unuse();

	// Swap between windows
	_window.SwapBuffer();
}

void FlappyBird::DrawSprites() {
	// Draw Background
	glm::vec4 background_pos = _BACKGROUND.GetPosition();
	GameEngine::GLTexture background_texture = _BACKGROUND.GetTexture();
	GameEngine::Color background_color = _BACKGROUND.GetColor();
	glm::vec4 background_uv(0.0f, 0.0f, 1.0f, 1.0f);

	_sprite_batch.Draw(background_pos, background_uv, background_texture.id, 0.1f, background_color);

	// Draw Pipes
	for (const auto& pipe : _game_state_manager.GetPipes()) {
		glm::vec4 pipe_pos = pipe.GetPosition();
		GameEngine::GLTexture pipe_texture = pipe.GetTexture();
		GameEngine::Color pipe_color = pipe.GetColor();
		glm::vec4 pipe_uv(0.0f, 0.0f, 1.0f, 1.0f);

		_sprite_batch.Draw(pipe_pos, pipe_uv, pipe_texture.id, 0.2f, pipe_color);
	}

	// Draw Player
	glm::vec4 pos = _game_state_manager.GetPlayer().GetPosition();
	GameEngine::GLTexture texture = _game_state_manager.GetPlayer().GetTexture();
	GameEngine::Color color = _game_state_manager.GetPlayer().GetColor();
	glm::vec4 player_uv(0.0f, 0.0f, 1.0f, 1.0f);

	_sprite_batch.Draw(pos, player_uv, texture.id, 0.3f, color);

	// Draw Text Boxes
	_sprite_batch.DrawText(_text_manager);
}

void FlappyBird::InitSystems() {
	GameEngine::init();

	_window.Create("Flappy Bird", Consts::SCREEN_WIDTH, Consts::SCREEN_HEIGHT, GameEngine::FULLSCREEN);

	InitShaders();

	_sprite_batch.Init();

	// Create sprite sheet and textbox
	_text_manager.AddSpriteSheet("Textures/jimmy_jump/PNG/text_sprites1.png", 
								9, 
								10, 
								Consts::DEFAULT_COLOR,
								Consts::TEXT_SPRITE_SHEET_MAPPER);

	PrintInitInfo();
	AddOpeningScreenText(0, Consts::MESSAGE_TEXT_SIZE);
}

void FlappyBird::UpdateTextBoxes() {
	GameState current_game_state = _game_state_manager.GetGameState();

	_text_manager.ClearTextBoxes();
	
	if (current_game_state == GameState::DEAD) {
		AddDeadPlayerText(0, Consts::MESSAGE_TEXT_SIZE);
	}

	if (current_game_state == GameState::OPENING_SCREEN) {
		AddOpeningScreenText(0, Consts::MESSAGE_TEXT_SIZE);
	}

	if (current_game_state == GameState::PLAY) {
		AddScoreText(0, Consts::SCORE_TEXT_SIZE, _game_state_manager.GetScore());
	}

	AddFrameCountText(0, Consts::SCORE_TEXT_SIZE, _game_state_manager.GetFrameCount());
}

void FlappyBird::AddDeadPlayerText(size_t spritesheet_index, float text_size) {
	_text_manager.AddTextBox(spritesheet_index, 
							 Consts::DEAD_PLAYER_TEXT_POS, 
							 "GAME OVER, PRESS Q TO RESTART!", 
							 text_size);
}

void FlappyBird::AddOpeningScreenText(size_t spritesheet_index, float text_size) {
	_text_manager.AddTextBox(spritesheet_index, 
							 Consts::OPENING_TEXT_POS, 
							 "PRESS SPACE TO START PLAYING!", 
							 text_size);
}

void FlappyBird::AddScoreText(size_t spritesheet_index, float text_size, size_t score) {
	std::stringstream ss;
	ss << score;

	_text_manager.AddTextBox(spritesheet_index,
							 Consts::SCORE_TEXT_POS,
							 ss.str(),
							 text_size);
}

void FlappyBird::PrintInitInfo() const {
	std::cout << Consts::START_MESSAGE;

	std::cout << "{";

	std::cout << "\"gravity\": " << Consts::GRAVITY << ",";
	std::cout << "\"player_jump_velo\": " << Consts::JUMP_VELOCITY << ",";
	//std::cout << "\"end_message_string\": " << Consts::END_MESSAGE << ",";
	//std::cout << "\"start_message_string\": " << Consts::START_MESSAGE << ",";
	std::cout << "\"max_height\": " << Consts::SCREEN_HEIGHT << ",";
	std::cout << "\"max_width\": " << Consts::SCREEN_WIDTH - Consts::PLAYER_INITIAL_POSITION.x + Consts::PIPE_WIDTH;


	std::cout << "}";

	std::cout << Consts::END_MESSAGE;
}

void FlappyBird::AddFrameCountText(size_t spritesheet_index, float text_size, size_t frame_count) {
	std::stringstream ss;
	ss << frame_count;

	_text_manager.AddTextBox(spritesheet_index,
		Consts::FRAME_COUNT_TEXT_POS,
		ss.str(),
		text_size);
}

void FlappyBird::InitShaders() {
	_color_program.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_color_program.AddAttribute("vertexPosition");
	_color_program.AddAttribute("vertexColor");
	_color_program.AddAttribute("vertexUV");
	_color_program.LinkShaders();
}