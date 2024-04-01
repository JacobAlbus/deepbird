#pragma once

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <map>

#include "GLTexture.h"
#include "Timing.h"
#include "Vertex.h"
#include "ResourceManager.h"

namespace GameEngine {


    class Spritesheet {
    public:
        Spritesheet(const std::string& texture_file_path,
                    const Color& color,
                    int row_count,
                    int col_count);

        glm::vec4 GetSpriteUVCoords(int x, int y) const;

        const Color& GetColor() const { return _color; }

        GLTexture GetTexture() const {
            return ResourceManager::GetTexture(_TEXTURE_FILE_PATH);
        }

    private:

        Color _color;
        const int _ROW_COUNT;
        const int _COL_COUNT;
        const std::string _TEXTURE_FILE_PATH;

    };

}