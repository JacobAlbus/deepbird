#pragma once

#include "TextBox.h"

namespace GameEngine {

	class TextManager {

	public:

		TextManager();

		void AddSpriteSheet(const std::string& texture_file_path,
							int row,
							int column,
							const Color& color,
							const std::map<char, glm::vec2>& sprite_sheet_mapper);

		void AddTextBox(size_t _sprite_sheet_index,
						const glm::vec2& bottom_left_corner,
						const std::string& initial_text, 
						float text_size);

		void ClearTextBoxes();

		const std::vector<std::pair<TextBox, size_t>> GetTextBoxes() const { return _textboxes; }

		const std::vector<Spritesheet>& GetSpriteSheets() const { return _spritesheets; }
		const std::vector<std::map<char, glm::vec2>>& GetSpriteSheetMappers() const { return _sprite_sheet_mappers; }

	private:

		std::vector<Spritesheet> _spritesheets;
		std::vector<std::map<char, glm::vec2>> _sprite_sheet_mappers;
		std::vector<std::pair<TextBox, size_t>> _textboxes;

		size_t _spritesheet_count;
	};

}