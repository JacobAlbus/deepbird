#include "ResourceManager.h"

namespace GameEngine {

	TextureCache ResourceManager::_texture_cache_;

	GLTexture ResourceManager::GetTexture(const std::string& texture_path) {
		return _texture_cache_.GetTexture(texture_path);
	}

}