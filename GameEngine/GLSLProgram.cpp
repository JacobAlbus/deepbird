#include "GLSLProgram.h"
#include "Errors.h"
#include "Helpers.h"

#include <vector>
#include <fstream>

namespace GameEngine {

	GLSLProgram::GLSLProgram() : _num_attributes(0), _program_id(0), _vertex_shader_id(0),
		_fragment_shader_id(0) {

	}

	GLSLProgram::~GLSLProgram() {

	}

	void GLSLProgram::AddAttribute(const std::string& attribute_name) {
		glBindAttribLocation(_program_id, _num_attributes, attribute_name.c_str());
		_num_attributes++;
	}

	void GLSLProgram::CompileShaders(const std::string& vertex_shader_file_path,
		const std::string& fragment_shader_file_path) {

		_program_id = glCreateProgram();

		_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
		if (_vertex_shader_id == 0) {
			Helpers::FatalError("Vertex shader failed to be created!");
		}

		_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragment_shader_id == 0) {
			Helpers::FatalError("Fragment shader failed to be created!");
		}

		CompileShader(vertex_shader_file_path, _vertex_shader_id);
		CompileShader(fragment_shader_file_path, _fragment_shader_id);
	}

	void GLSLProgram::LinkShaders() {
		glAttachShader(_program_id, _vertex_shader_id);
		glAttachShader(_program_id, _fragment_shader_id);

		glLinkProgram(_program_id);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_program_id, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> error_log(maxLength);
			glGetProgramInfoLog(_program_id, maxLength, &maxLength, &error_log[0]);

			// We don't need the program anymore.
			glDeleteProgram(_program_id);

			// Don't leak shaders either.
			glDeleteShader(_vertex_shader_id);
			glDeleteShader(_fragment_shader_id);

			std::printf("%s\n", &(error_log[0]));
			Helpers::FatalError("Shaders failed to link!");
		}

		glDetachShader(_program_id, _fragment_shader_id);
		glDetachShader(_program_id, _fragment_shader_id);

		glDeleteShader(_vertex_shader_id);
		glDeleteShader(_fragment_shader_id);
	}

	void GLSLProgram::CompileShader(const std::string& file_path, GLuint id) {
		std::string vertex_file_contents = Helpers::ReadFile(file_path);

		// Initialize and compile shader
		const char* contents_ptr = vertex_file_contents.c_str();
		glShaderSource(id, 1, &contents_ptr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		// Handle errors
		if (success == GL_FALSE) {
			GLint max_length = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<char> error_log(max_length);
			glGetShaderInfoLog(id, max_length, &max_length, &error_log[0]);

			std::printf("%s\n", &(error_log[0]));
			Helpers::FatalError("Shader " + file_path + " failed to compile!");
		}
	}

	GLint GLSLProgram::GetUniformLocation(const std::string& uniform_name) {
		GLint location = glGetUniformLocation(_program_id, uniform_name.c_str());

		if (location == GL_INVALID_INDEX) {
			Helpers::FatalError("Uniform " + uniform_name + " not found in shader!");
		}

		return location;
	}

	void GLSLProgram::Use() {
		glUseProgram(_program_id);

		for (int i = 0; i < _num_attributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::Unuse() {
		glUseProgram(0);

		for (int i = 0; i < _num_attributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}

}