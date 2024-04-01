#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Helpers.h"

namespace GameEngine {

	GLTexture ImageLoader::LoadPNG(const std::string& file_path) {
		std::vector<unsigned char> out;
		std::vector<unsigned char> in;

		unsigned long width, height;

		if (IOManager::ReadFileToBuffer(file_path, in) == false) {
			Helpers::FatalError("Failed to load PNG " + file_path + " to buffer!");
		}

		int error_code = decodePNG(out, width, height, &(in[0]), in.size());
		if (error_code != 0) {
			Helpers::FatalError("decodePNG failed wtih error: " + std::to_string(error_code));
		}

		// Instantiate texture
		GLTexture texture = {};
		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}

}