#pragma once

#include <string>
#include <glm/glm.hpp>

#include <GameEngine/Vertex.h>
#include <GameEngine/GLTexture.h>
#include <FlappyBird/Bird.h>
#include <GameEngine/Sprite.h>

class Pipe : public GameEngine::Sprite {

public:

	Pipe(const std::string& texture_file_path, 
		 const glm::vec4& initial_position,
		 const GameEngine::Color& color);

	Pipe(const Pipe& other_pipe);

	Pipe& operator=(const Pipe& rhs);

	bool IsTouchingPlayer(const Bird& player) const;

	void MovePipe(float distance);

private:

	
};

