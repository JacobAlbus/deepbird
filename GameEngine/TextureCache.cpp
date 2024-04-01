#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

namespace GameEngine {

	TextureCache::TextureCache() {

	}

	GLTexture TextureCache::GetTexture(const std::string& texture_path) {
		auto iterator = _texture_map.find(texture_path);

		// If not found, load texture and add to map
		if (iterator == _texture_map.end()) {
			GLTexture new_texture = ImageLoader::LoadPNG(texture_path);
			_texture_map.insert(make_pair(texture_path, new_texture));

			return new_texture;
		}

		return iterator->second;
	}

}