#include "tiler.h"
#include <SDL2_image/SDL_image.h>

/*
 * A library for drawing 2D tilemaps using SDL
 */

namespace tiler {
    Map::Map(){
        this->map = nullptr;
        this->renderer = nullptr;
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
        if(this->renderer == nullptr) { throw new ExNoRenderer(); }
        
        // Load image files
        const std::vector<Tmx::Tileset*>& tileSets = map->GetTilesets();
        for(int i = 0; i < tileSets.size(); ++i) {
            const Tmx::Tileset * tileSet = tileSets[i];
            const Tmx::Image * image = tileSet->GetImage();
            const std::string source = image->GetSource();
            SDL_RWops * rwop = SDL_RWFromFile(source.c_str(),"r");
            SDL_Surface * surf = IMG_LoadPNG_RW(rwop);
            SDL_Texture * tex = SDL_CreateTextureFromSurface(this->renderer, surf);
            this->images.push_back(tex);
        }
    }
    void Map::setRenderer(SDL_Renderer * r){
        this->renderer = r;
    }
    void Map::drawMap(int x_offset, int y_offset) {
        
    }

    /*
     * Exception Classes
     */

    const char* ExNoRenderer::what() const _NOEXCEPT {
        return "Renderer has not been set";
    } 
}
