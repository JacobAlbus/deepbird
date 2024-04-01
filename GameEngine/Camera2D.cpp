#include "Camera2D.h"

#include <iostream>

namespace GameEngine {

	Camera2D::Camera2D() : 
		_position(0.0f, 0.0f), 
		_camera_matrix(1.0f), 
		_ortho_matrix(1.0f),
		_scale(1.0f),
		_needs_matrix_update(true),
		_screen_width(1920),
		_screen_height(1080) {

	}

	void Camera2D::Init(int screen_width, int screen_height) {
		_screen_width = screen_width;
		_screen_height = screen_height;
		_ortho_matrix = glm::ortho(0.0f, (float)_screen_width, 0.0f, (float)_screen_height);
	}

	void Camera2D::Update() {
		if (_needs_matrix_update) {
			glm::vec3 translate(-_position.x, -_position.y, 0.0f);
			_camera_matrix = glm::translate(_ortho_matrix, translate);

			glm::vec3 scale(_scale, _scale, 0.0f);
			_camera_matrix = glm::scale(_camera_matrix, scale);

			_needs_matrix_update = false;
		}
		 
		
	}

}