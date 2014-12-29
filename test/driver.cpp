#include "SDL2/SDL.h"
#include <iostream>

#include "../src/tiler.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

using namespace tiler;

/*
 * A test program for the tiler functionality
 */

SDL_Renderer * setup() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Error: Could not initialize SDL" << std::endl;
    }
    SDL_Window *win = SDL_CreateWindow("Test", 100, 100, 
                                        WINDOW_WIDTH, WINDOW_HEIGHT, 
                                        SDL_WINDOW_SHOWN);
    if(win == nullptr){
        std::cout << "Error: Could not create window" << std::endl;
        SDL_Quit();
    }

    SDL_Renderer *ren = SDL_CreateRenderer( win, -1, 
                                            SDL_RENDERER_ACCELERATED | 
                                            SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr){
        std::cout << "Error: Could not create renderer" << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    return ren;
}

void teardown() {
    SDL_Quit();
}

void test(const std::string testName, bool passed) {
    if(passed) {
        std::cout << "[Passed]: " << testName << std::endl;
    }
    else {
        std::cout << "[Failed]: " << testName << std::endl;
    }
}

bool testLoadFromFile(SDL_Renderer * r) {
    tiler::Map map;
    map.setRenderer(r);
    try {
        map.loadFromFile("test/example.tmx");
    } catch(std::string err) {
        std::cout << err << std::endl;
        return false;
    } catch(ExNoRenderer* e){
        std::cout << e->what() << std::endl;
    }    
    return true;
}

bool testFileOpen() {
    const std::string fileName = "test/example.tmx";
    FILE *file = fopen(fileName.c_str(), "rb");
    if(!file) { 
        std::cout << strerror(errno) << std::endl;
        return false; 
    }
    else { 
        fclose(file);
        return true; 
    }
}

bool testLoadImages(SDL_Renderer* r) {
    tiler::Map map;
    map.setRenderer(r);
    try {
        map.loadFromFile("test/example.tmx");
        if(map.numImages() != 1) { 
            std::cout << "Number of images is:" << map.numImages() << std::endl;
            return false; 
        }
    } catch(std::string err) {
        std::cout << err << std::endl;
        return false;
    } catch(ExNoRenderer* e){
        std::cout << e->what() << std::endl;
    }  
    return true;

}

int main(int argc, char ** argv) {
    SDL_Renderer * renderer = setup();
    
    test("Open tmx file", testFileOpen());
    test("Load tmx file", testLoadFromFile(renderer));
    test("Load image files into map object" ,testLoadImages(renderer));

    /*
    SDL_Event e;
    bool quit = false;
    while(quit == false){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }
    }
    */

    teardown();
    return 0;
}
