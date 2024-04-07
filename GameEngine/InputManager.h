#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace GameEngine {

class InputManager {

public:

	InputManager();

	void PressKey(unsigned int key_id);

	void ReleaseKey(unsigned int key_id);

	unsigned int AwaitInput() const;

	bool IsKeyPressed(unsigned int key_id);

	void SetMouseCoords(float x, float y);

	const glm::vec2& GetMouseCoords() const;

private:

	glm::vec2 _mouse_coords;

	std::unordered_map<unsigned int, bool> _key_map;
};

}