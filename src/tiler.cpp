#include "tiler.h"
#include <SDL2_image/SDL_image.h>
// #include <iostream> // DEBUGGING

/*
 * A library for drawing 2D tilemaps using SDL
 */

namespace tiler {
    Map::Map(){
        int flags = IMG_Init(IMG_INIT_PNG);
        if(flags != IMG_INIT_PNG) {
            // Error condition
        }
    }
    Map::~Map(){
    
    }
    int Map::numImages() {
        return images.size();
    }
    void Map::loadFromFile(const std::string filename){
        map = new Tmx::Map();
        map->ParseFile(filename);

        if(map->HasError() == true) { throw map->GetErrorText(); }
        
        // Load image files
        const std::vector<Tmx::Tileset*>& tileSets = map->GetTilesets();
        for(int i = 0; i < tileSets.size(); ++i) {
            const Tmx::Tileset * tileSet = tileSets[i];
            const Tmx::Image * image = tileSet->GetImage();
            const std::string source = image->GetSource();
            SDL_RWops * rwop = SDL_RWFromFile(source.c_str(),"r");
            SDL_Surface * surf = IMG_LoadPNG_RW(rwop);
            this->images.push_back(surf);
        }
    }
    void Map::registerRenderer(SDL_Renderer * r){
        this->renderer = r;
    }
    void Map::drawMap(int x_offset, int y_offset) {
        
    }
}
