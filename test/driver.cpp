#include "SDL2/SDL.h"
#include <iostream>

#include "../src/tiler.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

/*
 * A test program for the tiler functionality
 */

int main(int argc, char ** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Test", 100, 100, 
                                        WINDOW_WIDTH, WINDOW_HEIGHT, 
                                        SDL_WINDOW_SHOWN);
    if(win == nullptr){
        SDL_Quit();
        return 2;
    }

    SDL_Renderer *ren = SDL_CreateRenderer( win, -1, 
                                            SDL_RENDERER_ACCELERATED | 
                                            SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr){
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 3;
    }
    

    SDL_Event e;
    bool quit = false;
    while(quit == false){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }
    }

    SDL_Quit();
    return 0;
}
