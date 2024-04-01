#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace GameEngine {

	Sprite::Sprite() : _vboID(0) {

	}

	Sprite::~Sprite() {
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::init(float x, float y, float width, float height, const std::string& texture_path) {
		//_x = x;
		//_y = y;
		//_width = width;
		//_height = height;

		//_texture = ResourceManager::GetTexture(texture_path);

		//// Initialize Vertex Buffer Object
		//if (_vboID == 0) {
		//	glGenBuffers(1, &_vboID);
		//}

		//// Define vertices for 2 triangles which form a rectangle
		//const size_t kVertexCount = 6;
		//Vertex vertex_data[kVertexCount];

		//// First triangle
		//vertex_data[0].SetPosition(x + width, y + height);
		//vertex_data[0].SetUV(1.0f, 1.0f);

		//vertex_data[1].SetPosition(x, y + height);
		//vertex_data[1].SetUV(0.0f, 1.0f);

		//vertex_data[2].SetPosition(x, y);
		//vertex_data[2].SetUV(0.0f, 0.0f);

		//// Second triangle
		//vertex_data[3].SetPosition(x, y);
		//vertex_data[3].SetUV(0.0f, 0.0f);

		//vertex_data[4].SetPosition(x + width, y);
		//vertex_data[4].SetUV(1.0f, 0.0f);

		//vertex_data[5].SetPosition(x + width, y + height);
		//vertex_data[5].SetUV(1.0f, 1.0f);

		//// Set Colors
		//for (size_t index = 0; index < kVertexCount; index++) {
		//	vertex_data[index].SetColor(255, 0, 255, 255);
		//}
		//vertex_data[1].SetColor(0, 0, 255, 255);
		//vertex_data[4].SetColor(0, 255, 0, 255);

		//// Bind vertex to Vertex Buffer Object (sends data to gpu)
		//glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

		//// Unbind the buffer
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw() const {

		glBindTexture(GL_TEXTURE_2D, _texture.id);

		// Bind buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

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

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Unbind buffer object
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}