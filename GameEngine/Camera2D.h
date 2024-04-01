#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace GameEngine {

	class Camera2D {

	public:
		Camera2D();

		void Update();

		void Init(int screen_width, int screen_height);

		// Setters
		void SetPosition(glm::vec2 new_position) { 
			_needs_matrix_update = true;  
			_position = new_position; 
		}

		void SetScale(float new_scale) { 
			_needs_matrix_update = true;
			_scale = new_scale;  
		}

		// Getters
		const glm::vec2& GetPosition() const { return _position; }

		float GetScale() const { return _scale; }

		const glm::mat4& GetCameraMatrix() const { return _camera_matrix; }

	private:

		int _screen_width;
		int _screen_height;
		float _scale;

		glm::vec2 _position;
		glm::mat4 _camera_matrix;
		glm::mat4 _ortho_matrix;

		bool _needs_matrix_update;
	};

}

