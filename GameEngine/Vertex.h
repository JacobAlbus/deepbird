#pragma once

#include <GL/glew.h>

namespace GameEngine {

	struct Color {

		Color() : r(0), b(0), g(0), a(0) {}

		Color(
			GLubyte r, 
			GLubyte b, 
			GLubyte g, 
			GLubyte a) :
			r(r), 
			b(b), 
			g(g), 
			a(a) {}

		GLubyte r;
		GLubyte b;
		GLubyte g;
		GLubyte a;
	};

	struct Position {
		Position() : x(0), y(0) {}

		float x;
		float y;
	};

	struct UV {
		UV() : u(0), v(0) {}

		float u;
		float v;
	};

	struct Vertex {

		Vertex() : position(Position()), color(Color()), uv(UV()) {};

		Position position;

		Color color;

		// UV texture coordinates
		UV uv;

		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void SetPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void SetUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};

}