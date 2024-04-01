#include "SpriteBatch.h"

#include <algorithm>
#include <iostream>
#include "GLTexture.h"

namespace GameEngine {

	SpriteBatch::SpriteBatch() : _vbo(0), _vao(0), _sort_type(GlyphSortType::TEXTURE) {

	}

	SpriteBatch::~SpriteBatch() {
		for (size_t index = 0; index < _glyphs.size(); index++) {
			delete _glyphs[index];
		}
	}

	void SpriteBatch::Init() {
		CreateRenderBatches();
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sort_type) {
		_sort_type = sort_type;
		_render_batches.clear();

		for (size_t index = 0; index < _glyphs.size(); index++) {
			delete _glyphs[index];
		}
		_glyphs.clear();
	}

	void SpriteBatch::End() {
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destination_rect, const glm::vec4& uv_rect, GLuint texture, float depth, Color color) {
		Glyph* new_glyph = new Glyph;
		new_glyph->_texture = texture;
		new_glyph->_depth = depth;

		new_glyph->_top_left.color = color;
		new_glyph->_top_left.SetPosition(destination_rect.x, destination_rect.y + destination_rect.w);
		new_glyph->_top_left.SetUV(uv_rect.x, uv_rect.y + uv_rect.w);

		new_glyph->_bottom_left.color = color;
		new_glyph->_bottom_left.SetPosition(destination_rect.x, destination_rect.y);
		new_glyph->_bottom_left.SetUV(uv_rect.x, uv_rect.y);

		new_glyph->_bottom_right.color = color;
		new_glyph->_bottom_right.SetPosition(destination_rect.x + destination_rect.z, destination_rect.y);
		new_glyph->_bottom_right.SetUV(uv_rect.x + uv_rect.z, uv_rect.y);

		new_glyph->_top_right.color = color;
		new_glyph->_top_right.SetPosition(destination_rect.x + destination_rect.z, destination_rect.y + destination_rect.w);
		new_glyph->_top_right.SetUV(uv_rect.x + uv_rect.z, uv_rect.y + uv_rect.w);
	
		_glyphs.push_back(new_glyph);
	}

	void SpriteBatch::DrawText(const TextManager& text_manager) {
		for (const auto& pair : text_manager.GetTextBoxes()) {
			TextBox textbox = pair.first;
			size_t sprite_sheet_index = pair.second;

			int x_offset = 0;

			glm::vec2 bottom_left_corner = textbox.GetBottomLeftCorner();
			float text_size = textbox.GetTextSize();

			const std::map<char, glm::vec2>& sprite_sheet_mapper = text_manager.GetSpriteSheetMappers()[sprite_sheet_index];
			Spritesheet sprite_sheet = text_manager.GetSpriteSheets()[sprite_sheet_index];

			for (char current_char : textbox.GetChars()) {
				glm::vec4 char_position(bottom_left_corner.x + x_offset, bottom_left_corner.y, text_size, text_size);

				auto iterator = sprite_sheet_mapper.find(current_char);

				// If found, write char to screen. Else write space to screen (i.e. don't do anything)
				if (iterator != sprite_sheet_mapper.end()) {
					glm::vec2 coords = iterator->second;

					glm::vec4 uv_rect = sprite_sheet.GetSpriteUVCoords((int) coords.x, (int) coords.y);
					Color char_color = sprite_sheet.GetColor();
					GLTexture texture = sprite_sheet.GetTexture();

					Draw(char_position, uv_rect, texture.id, 0.4f, char_color);
				}

				x_offset += text_size;
			}
		}
	}

	void SpriteBatch::RenderBatches() {
		glBindVertexArray(_vao);

		for (size_t index = 0; index < _render_batches.size(); index++) {
			glBindTexture(GL_TEXTURE_2D, _render_batches[index]._texture);

			glDrawArrays(GL_TRIANGLES, _render_batches[index]._offset, _render_batches[index]._num_verticies);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::CreateVertexArray() {
		if (_vao == 0) {
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);

		if (_vbo == 0) {
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// Tell opengl to use the first attribute array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Points to position attribute
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		// Points to color attribute
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		// Points to UV attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// Unbind VAO and VBO
		glBindVertexArray(0);
	}

	void SpriteBatch::CreateRenderBatches() {
		if (_glyphs.empty()) {
			return;
		}

		// Each sprite is a rectangle, which is just two triangles, so there are 6 vertices total
		const int NUM_VERTICIES = 6;

		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * NUM_VERTICIES);

		int offset = 0;
		_render_batches.emplace_back(offset, NUM_VERTICIES, _glyphs[0]->_texture);
	
		int current_vertex = 0;
		vertices[current_vertex++] = _glyphs[0]->_top_left;
		vertices[current_vertex++] = _glyphs[0]->_bottom_left;
		vertices[current_vertex++] = _glyphs[0]->_bottom_right;
		vertices[current_vertex++] = _glyphs[0]->_bottom_right;
		vertices[current_vertex++] = _glyphs[0]->_top_right;
		vertices[current_vertex++] = _glyphs[0]->_top_left;

		for (size_t current_glyph = 1; current_glyph < _glyphs.size(); current_glyph++) {
			vertices[current_vertex++] = _glyphs[current_glyph]->_top_left;
			vertices[current_vertex++] = _glyphs[current_glyph]->_bottom_left;
			vertices[current_vertex++] = _glyphs[current_glyph]->_bottom_right;
			vertices[current_vertex++] = _glyphs[current_glyph]->_bottom_right;
			vertices[current_vertex++] = _glyphs[current_glyph]->_top_right;
			vertices[current_vertex++] = _glyphs[current_glyph]->_top_left;

			offset += NUM_VERTICIES;

			if (_glyphs[current_glyph]->_texture != _glyphs[current_glyph - 1]->_texture) {
				_render_batches.emplace_back(offset, NUM_VERTICIES, _glyphs[current_glyph]->_texture);
			}
			else {
				_render_batches.back()._num_verticies += NUM_VERTICIES;
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	
		// upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::SortGlyphs() {
		switch (_sort_type) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareTexture);
			break;
		}
	}

	bool SpriteBatch::CompareFrontToBack(const Glyph* a, const Glyph* b) {
		return (a->_depth < b->_depth);
	}

	bool SpriteBatch::CompareBackToFront(const Glyph* a, const Glyph* b) {
		return (a->_depth > b->_depth);
	}

	bool SpriteBatch::CompareTexture(const Glyph* a, const Glyph* b) {
		return (a->_texture < b->_texture);
	}
}