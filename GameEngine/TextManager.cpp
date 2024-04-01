#include "TextManager.h"

#include "Helpers.h"

namespace GameEngine {

	TextManager::TextManager() : _spritesheet_count(0) {

	}

	void TextManager::AddSpriteSheet(const std::string& texture_file_path,
									int row,
									int column,
									const Color& color,
									const std::map<char, glm::vec2>& sprite_sheet_mapper) {

		_spritesheets.emplace_back(texture_file_path, color, row, column);
		_sprite_sheet_mappers.emplace_back(sprite_sheet_mapper);
		_spritesheet_count++;
	}

	void TextManager::AddTextBox(size_t sprite_sheet_index,
								 const glm::vec2& bottom_left_corner,
								 const std::string& initial_text,
								 float text_size) {

		if (sprite_sheet_index >= _spritesheet_count) {
			GameEngine::Helpers::FatalError("Invalid sprite sheet index selected");
		}

		TextBox new_textbox(bottom_left_corner, initial_text, text_size);
		_textboxes.emplace_back(new_textbox, sprite_sheet_index);
	}

	void TextManager::ClearTextBoxes() {
		_textboxes.clear();
	}

}