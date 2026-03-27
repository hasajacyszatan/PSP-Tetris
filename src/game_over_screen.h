#pragma once
#include <SDL.h>
#include <pspctrl.h>
#include "background.h"

class GameOverScreen {
private:
    Background* bg;
    SDL_Renderer* renderer;
    SDL_Texture*  texture;
    SDL_Texture*  imageTexture;
    SDL_Rect      rect;
    SDL_Rect      imgRect;

public:
    GameOverScreen(SDL_Renderer* renderer, Background* bg);
    ~GameOverScreen();

    int render();
    int draw(const SceCtrlData& pad);
};
