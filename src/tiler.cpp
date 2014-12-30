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
        this->map = new Tmx::Map();
        this->map->ParseFile(filename);

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
        const std::vector<Tmx::Layer*> &layers = this->map->GetLayers();
        int layerWidth = 0;
        int layerHeight = 0;
        int tileId = 0;
        int tilePos = 0;
        int tileSetIndex = 0;
        Tmx::Layer* layer;
        SDL_Rect drawDest;
        SDL_Rect drawSrc;
        int tileWidth = map->GetTileWidth();
        int tileHeight = map->GetTileHeight();

        for(int i = 0; i < layers.size(); ++i){
            layer = layers[i];
            layerWidth = layer->GetWidth();
            layerHeight = layer->GetHeight();
            for(int y = 0; y < layerHeight; ++y){
                for(int x = 0; x < layerWidth; ++x){
                    tileId = layer->GetTileId(x, y);
                    tileSetIndex = layer->GetTileTilesetIndex(x,y);
                    tilePos = this->map->FindTilesetIndex(tileId);

                    drawSrc.x = tilePos % layerWidth;
                    drawSrc.y = tilePos / layerWidth;

                    drawDest.x = x;
                    drawDest.y = y;

                    SDL_RenderCopy(this->renderer, this->images[tileSetIndex], &drawSrc, &drawDest);
                }
            }
        }
    }

    /*
     * Exception Classes
     */

    const char* ExNoRenderer::what() const _NOEXCEPT {
        return "Renderer has not been set";
    } 
}
