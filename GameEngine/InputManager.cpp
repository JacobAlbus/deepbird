#include "InputManager.h"

namespace GameEngine {
	InputManager::InputManager() {

	}

	InputManager::~InputManager() {

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

	void InputManager::SetMouseCoords(float x, float y) {
		_mouse_coords.x = x;
		_mouse_coords.y = y;
	}

	const glm::vec2& InputManager::GetMouseCoords() const {
		return _mouse_coords;
	}
}