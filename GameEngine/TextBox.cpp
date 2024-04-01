#include "TextBox.h"

namespace GameEngine {

	TextBox::TextBox(const glm::vec2& bottom_left_corner,
		const std::string& initial_text,
		float text_size) :
		_BOTTOM_LEFT_CORNER(bottom_left_corner),
		_text_size(text_size) {
		AddChars(initial_text);
	}

	//void TextBox::Draw(int text_size,
	//	const std::map<char, glm::vec2>& sprite_sheet_mapper,
	//	const Spritesheet& sprite_sheet) {

	//	int x_offset = 0;

	//	for (char current_char : _chars) {
	//		glm::vec4 char_position(_BOTTOM_LEFT_CORNER.x + x_offset, _BOTTOM_LEFT_CORNER.y, text_size, text_size);

	//		auto iterator = sprite_sheet_mapper.find(current_char);

	//		// If found, write char to screen. Else write space to screen (i.e. don't do anything)
	//		if (iterator != sprite_sheet_mapper.end()) {
	//			glm::vec2 coords = iterator->second;

	//			sprite_sheet.DrawSprite(5, 5, char_position);
	//		}

	//		x_offset += text_size;
	//	}
	//}

	void TextBox::AddChars(const std::string& added_string) {
		for (char added_char : added_string) {
			AddChar(added_char);
		}
	}

	void TextBox::AddChar(char added_char) {
		_chars.emplace_back(added_char);
	}

}