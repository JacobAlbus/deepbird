#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
 
#include "GLTexture.h"
#include "Timing.h"
#include "Vertex.h"
#include "ResourceManager.h"

namespace GameEngine {

	class Sprite {

	public:
		Sprite(const std::string& texture_file_path, 
			   const glm::vec4& position, 
			   const Color& color) : 
			_TEXTURE_FILE_PATH(texture_file_path),
			_position(position),
			_color(color)
		{};

		const glm::vec4& GetPosition() const { return _position; }

		const Color GetColor() const { return _color; }

		const std::string& GetTextureFilePath() const { return _TEXTURE_FILE_PATH; }

		GLTexture GetTexture() const {
			return ResourceManager::GetTexture(_TEXTURE_FILE_PATH);
		}

		// X1 is bottom left corner x-coord, Y1 is bottom left corner y-coord
		// X2 is top right corner x-coord, Y2 is top right corner y-coord
		float GetX1() const { return _position.x; }
		float GetY1() const { return _position.y; }
		float GetX2() const { return _position.x + _position.z; }
		float GetY2() const { return _position.y + _position.w; }

		float GetHeight() const { return _position.w; }
		float GetWidth() const { return _position.z; }

		bool IsCoordBetweenX(float coord) const {
			return (coord >= GetX1()) && (coord <= GetX2());
		}

		bool IsCoordBetweenY(float coord) const {
			return (coord >= GetY1()) && (coord <= GetY2());
		}

		bool IsOffScreen(int screen_width, int screen_height) const {
			return (GetX2() < 0) || (GetY2() < 0) || (GetY1() > screen_height) || (GetX1() > screen_width);
		}

	protected:
		const std::string _TEXTURE_FILE_PATH;
		glm::vec4 _position;
		Color _color;
	};

}