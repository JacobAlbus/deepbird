#include "InputManager.h"

#include <iostream>

namespace GameEngine {
	InputManager::InputManager() : _mouse_coords(glm::vec2()) {

	}

	void InputManager::PressKey(unsigned int key_id) {
		_key_map[key_id] = true;
	}

	void InputManager::ReleaseKey(unsigned int key_id) {
		_key_map[key_id] = false;
	}

	bool InputManager::IsKeyPressed(unsigned int key_id) {
		auto iterator = _key_map.find(key_id);

		if (iterator != _key_map.end()) {
			return iterator->second;
		} else {
			return false;
		}
	}

	unsigned int InputManager::AwaitInput() const {
		unsigned int input;
		std::cin >> input;
		return input;
	}

	void InputManager::SetMouseCoords(float x, float y) {
		_mouse_coords.x = x;
		_mouse_coords.y = y;
	}

	const glm::vec2& InputManager::GetMouseCoords() const {
		return _mouse_coords;
	}
}