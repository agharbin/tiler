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
            std::vector<SDL_Surface*> images;
            SDL_Renderer * renderer;
        public:
            Map();
            ~Map();
            void loadFromFile(const std::string);
            void drawMap(int x_offset, int y_offset);
            void registerRenderer(SDL_Renderer *);
            int numImages();
    };
}

#endif
