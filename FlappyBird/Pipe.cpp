#include "Pipe.h"

#include <GameEngine/ResourceManager.h>

Pipe::Pipe(
	const std::string& texture_file_path,
	const glm::vec4& initial_position,
	const GameEngine::Color& color) : 
	Sprite(texture_file_path, initial_position, color)  {

}

Pipe::Pipe(const Pipe& other_pipe) : 
	Sprite(other_pipe.GetTextureFilePath(), 
		   other_pipe.GetPosition(),
		   other_pipe.GetColor()) {}

Pipe& Pipe::operator=(const Pipe& rhs) {
	Pipe new_pipe(rhs);
	return new_pipe;
}

void Pipe::MovePipe(float distance) {
	_position.x += distance;
}

bool Pipe::IsTouchingPlayer(const Bird& player) const {
	float nib = player.GetX1();
	float nib1 = GetX1();
	float nib2 = GetX2();
	float nib3 = player.GetY1();
	float nib4 = player.GetY2();
	float nib5 = GetY1();
	float nib6 = GetY2();

	bool is_inbetweenX = IsCoordBetweenX(player.GetX1()) || IsCoordBetweenX(player.GetX2());
	bool is_inbetweenY = IsCoordBetweenY(player.GetY1()) || IsCoordBetweenY(player.GetY2());

	return is_inbetweenX && is_inbetweenY;
}