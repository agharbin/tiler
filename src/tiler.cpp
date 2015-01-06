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
    void Map::drawTile(int guid, int tileset_i, int x, int y) {
        SDL_Rect dst, src;
        int tile_w = this->map->GetTileWidth();
        int tile_h = this->map->GetTileHeight();

        const Tmx::Tileset* ts = this->map->GetTileset(tileset_i);
        int img_w_tiles = ts->GetImage()->GetWidth() / tile_w;

        int spacing = ts->GetSpacing();
        int tile_pos = guid - ts->GetFirstGid() + 1; // first GUID is 1, not 0

        // Get pixel boundaries of this tile adjusting for tile borders
        src.x = (tile_pos % img_w_tiles) * (tile_w + spacing) + spacing;
        src.y = (tile_pos / img_w_tiles) * (tile_h + spacing) + spacing;
              
        src.w = dst.w = tile_w;
        src.h = dst.h = tile_h;

        dst.x = x;
        dst.y = y;

        SDL_RenderCopy(this->renderer, this->images[tileset_i], &src, &dst);
    }
    void Map::drawMap(int x_offset, int y_offset, int scr_width, int scr_height) {
        const std::vector<Tmx::Layer*> &layers = this->map->GetLayers();
        int tile_id = 0;
        int tileset_i = -1;
        int tile_w = this->map->GetTileWidth();
        int tile_h = this->map->GetTileHeight();
        Tmx::Layer* layer;

        // Draw all layers from bottom to top.
        for(int i = 0; i < layers.size(); ++i){
            layer = layers[i];

            // Set tile edges of the layer portion to be drawn.
            int start_x = 0;
            int end_x = layer->GetWidth() - 1;
            int start_y = 0;
            int end_y = layer->GetHeight() - 1;

            // Clip off-screen map tiles.
            if(x_offset + scr_width < (layer->GetWidth() - 1) * tile_w) {
                end_x = (x_offset + scr_width) / tile_w;
            }
            if(y_offset + scr_height < (layer->GetHeight() - 1) * tile_h) {
                end_y = (y_offset + scr_height) / tile_h;
            }
            if(x_offset > tile_w) {
                start_x = x_offset / tile_w;
            }
            if(y_offset > tile_h) {
                start_y = y_offset / tile_h;
            }

            // Draw all tiles in this layer after clipping.
            for(int y = start_y; y <= end_y; ++y){
                for(int x = start_x; x <= end_x; ++x){
                    tile_id = layer->GetTile(x, y).id;
                    tileset_i = layer->GetTile(x,y).tilesetId;
                    int x_pos = x * tile_w - x_offset;
                    int y_pos = y * tile_h - y_offset;
                    if(tileset_i != -1){
                        this->drawTile(tile_id, tileset_i, x_pos, y_pos);
                    }
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
