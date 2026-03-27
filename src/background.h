#pragma once
#include <SDL.h>

class Background {
private:
    SDL_Renderer* renderer;
    SDL_Texture*  texture;
    SDL_Rect      rect;

public:
    Background(SDL_Renderer* renderer, const char* background_path);
    ~Background();
    int draw();
};
