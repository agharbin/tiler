#ifndef TILER_H
#define TILER_H

#include <string>
#include "tmxparser/Tmx.h"

/*
 * A library for drawing 2D tilemaps using SDL
 */

namespace tiler {
    class Map {
        private:
            Tmx::Map * map;
        public:
            Map();
            ~Map();
            void loadFromFile(const std::string);
    };
}

#endif
