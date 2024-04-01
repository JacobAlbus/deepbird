#pragma once

#include <string>
#include <GL/glew.h>

namespace GameEngine {

	class GLSLProgram {

	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string& vertex_shader_file_path,
			const std::string& fragment_shader_file_path);

		void LinkShaders();

		void AddAttribute(const std::string& attributeName);

		GLint GetUniformLocation(const std::string& uniform_name);

		void Use();

		void Unuse();

	private:


		void CompileShader(const std::string& file_path, GLuint id);

		int _num_attributes;

		GLuint _program_id;
		GLuint _vertex_shader_id;
		GLuint _fragment_shader_id;
	};

}