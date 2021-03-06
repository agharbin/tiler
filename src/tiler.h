#ifndef TILER_H
#define TILER_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "tmxparser/Tmx.h"

/*
 * A library for drawing 2D tilemaps using SDL
 */

namespace tiler {
    class Map {
        private:
            Tmx::Map * map;
            std::vector<SDL_Texture*> images;
            SDL_Renderer * renderer;

            void drawTile(int, int, int, int);
        public:
            Map();
            ~Map();
            void loadFromFile(const std::string);
            void drawMap(int ,int, int, int);
            void setRenderer(SDL_Renderer *);
            int numImages();
    };

    class ExNoRenderer : std::exception {
        public:
            const char* what() const _NOEXCEPT;
    };
}

#endif
