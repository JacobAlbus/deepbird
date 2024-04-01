#pragma once

#include "Vertex.h"
#include "TextManager.h"

#include <glm/glm.hpp>
#include <vector>

namespace GameEngine {

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Glyph {

	Glyph() : 
		_texture(0), 
		_depth(0.0f), 
		_top_left(Vertex()),
		_bottom_left(Vertex()), 
		_top_right(Vertex()), 
		_bottom_right(Vertex()) {}

	GLuint _texture;
	float _depth;

	Vertex _top_left;
	Vertex _bottom_left;
	Vertex _top_right;
	Vertex _bottom_right;
};

class RenderBatch {
public:

	RenderBatch(GLuint offset, GLuint num_vertices, GLuint texture) 
		: _offset(offset),
		_num_verticies(num_vertices),
		_texture(texture) { }

	GLuint _offset;
	GLuint _num_verticies;
	GLuint _texture;
};

class SpriteBatch {

public:

	SpriteBatch();
	~SpriteBatch();

	void Init();

	void Begin(GlyphSortType sort_type);

	void End();

	void Draw(const glm::vec4& destination_rect, const glm::vec4& uv_rect, GLuint texture, float depth, Color color);

	void DrawText(const TextManager& text_manager);

	void RenderBatches();

private:

	void CreateRenderBatches();

	void CreateVertexArray();

	void SortGlyphs();

	static bool CompareFrontToBack(const Glyph* a, const Glyph* b);
	static bool CompareBackToFront(const Glyph* a, const Glyph* b);
	static bool CompareTexture(const Glyph* a, const Glyph* b);

	GLuint _vbo;
	GLuint _vao;

	GlyphSortType _sort_type;
	
	std::vector<Glyph*> _glyphs;
	std::vector<RenderBatch> _render_batches;
};

}