#pragma once

#include <GameEngine/GLTexture.h>
#include <GameEngine/Vertex.h>
#include <GameEngine/Timing.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/InputManager.h>

#include <glm/glm.hpp>
#include <string>


class Bird : public GameEngine::Sprite {

public:

	Bird(const std::string& texture_file_path,
		 const glm::vec4& position,
		 const GameEngine::Color& color);

	void SetInitialPosition();

	void UpdatePosition(GameEngine::InputManager input_manager);

	// Keep player within screen boundaries
	void PreventScreenClipping();

	float GetVelocity() const { return _current_velocity; }

private:

	void UpdateVelocity(bool is_spacebar_pressed);

	GameEngine::Timer _timer;

	float _current_velocity = 0;
};

