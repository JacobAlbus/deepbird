#pragma once

#include "Spritesheet.h"

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <map>

namespace GameEngine {

class TextBox {

public:

	TextBox(const glm::vec2& bottom_left_corner, const std::string& initial_text, float text_size);

	/*void Draw(int text_size,
			  const std::map<char, glm::vec2>& sprite_sheet_mapper,
			  const Spritesheet& sprite_sheet);*/

	void AddChars(const std::string& added_string);

	void AddChar(char added_char);

	const std::vector<char>& GetChars() const { return _chars; }

	const glm::vec2& GetBottomLeftCorner() const { return _BOTTOM_LEFT_CORNER; }

	float GetTextSize() const { return _text_size; }

private:

	std::vector<char> _chars;

	float _text_size;

	const glm::vec2 _BOTTOM_LEFT_CORNER;
};

}