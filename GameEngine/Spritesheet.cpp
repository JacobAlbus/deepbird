#include "Spritesheet.h"

#include <glm/glm.hpp>
#include <SDL_Image/SDL_image.h>
#include <string>

namespace GameEngine {

    Spritesheet::Spritesheet(const std::string& texture_file_path,
        const Color& color,
        int row_count,
        int col_count) :

        _TEXTURE_FILE_PATH(texture_file_path),
        _color(color),
        _ROW_COUNT(row_count),
        _COL_COUNT(col_count) { }

    glm::vec4 Spritesheet::GetSpriteUVCoords(int x, int y) const {
        float sprite_width = 1 / (float) _COL_COUNT;
        float sprite_height = 1 / (float) _ROW_COUNT;
        float x_coord = sprite_width * x;
        float y_coord = sprite_height * y;

        return glm::vec4(x_coord, y_coord, sprite_width, sprite_height);
    }

}