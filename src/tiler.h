#ifndef TILER_H
#define TILER_H

#include <string>

/*
 * A library for drawing 2D tilemaps using SDL
 */

namespace tiler {
    class Map {
        public:
            Map();
            ~Map();
            static void loadFromFile(std::string);
    };
}

#endif
