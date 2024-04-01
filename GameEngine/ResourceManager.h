#pragma once

#include "TextureCache.h"
#include <string>

namespace GameEngine {

	class ResourceManager {

	public:

		static GLTexture GetTexture(const std::string& texture_path);

	private:

		static TextureCache _texture_cache_;
	};

}