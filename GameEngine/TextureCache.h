#pragma once

#include "GLTexture.h"

#include <map>
#include <string>

namespace GameEngine {

	class TextureCache {

	public:
		TextureCache();

		GLTexture GetTexture(const std::string& texture_path);

	private:
		std::map<std::string, GLTexture> _texture_map;
	};

}