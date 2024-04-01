#pragma once

#include "GLTexture.h"
#include <string>

namespace GameEngine {

	class ImageLoader {

	public:
		static GLTexture LoadPNG(const std::string& file_path);
	};

}