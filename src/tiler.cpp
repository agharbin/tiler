#include "tiler.h"

/*
 * A library for drawing 2D tilemaps using SDL
 */

namespace tiler {
    Map::Map(){
    
    }
    Map::~Map(){
    
    }
    void Map::loadFromFile(const std::string filename){
        map = new Tmx::Map();
        map->ParseFile(filename);
    }
}
