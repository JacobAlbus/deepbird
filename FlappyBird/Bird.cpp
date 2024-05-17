#include "Bird.h"

#include <GameEngine/ResourceManager.h>
#include "Constants.h"

#include <iostream>
#include <algorithm> 

Bird::Bird(
	const std::string& texture_file_path,
	const glm::vec4& position,
	const GameEngine::Color& color) : 
	Sprite(texture_file_path, position, color) {

	SetInitialPosition();
}

void Bird::SetInitialPosition() {
	_position = Consts::PLAYER_INITIAL_POSITION;
	_timer.StartTime();
	_current_velocity = 0;
}

void Bird::UpdatePosition(GameEngine::InputManager input_manager) {
	/*if (input_manager.IsKeyPressed(SDLK_w)) {
		_position.y += Consts::JUMP_VELOCITY;
	}
	if (input_manager.IsKeyPressed(SDLK_s)) {
		_position.y -= Consts::JUMP_VELOCITY;
	}*/

	UpdateVelocity(input_manager.IsKeyPressed(SDLK_SPACE));
	_position.y += _current_velocity;

	_timer.StartTime();
}

void Bird::UpdateVelocity(bool is_spacebar_pressed) {
	if (is_spacebar_pressed) {
		_current_velocity = Consts::JUMP_VELOCITY;
	} else {
		//float elapsed_time = _timer.GetElapsedTime();
		float elapsed_time = 0.016667;
		_current_velocity -= elapsed_time * Consts::GRAVITY;
	}
}

void Bird::PreventScreenClipping() {
  	_position.x = std::max(_position.x, 0.0f);
	_position.y = std::max(_position.y, 0.0f);

	_position.x = std::min(_position.x, Consts::SCREEN_WIDTH - GetWidth());
	_position.y = std::min(_position.y, Consts::SCREEN_HEIGHT - GetHeight());
}
    