#pragma once
#include <SDL.h>
#include <pspctrl.h>
#include "background.h"

class LevelSelector {
private:
    SDL_Renderer* renderer;
    Background*   bg;
    SDL_Rect      rect;
    SDL_Rect      rect2;
    int  running      = 0;
    bool clicked      = false;
    int  currentLevel = 0;

public:
    LevelSelector(SDL_Renderer* renderer, Background* bg);
    void draw();
    void handleinput(const SceCtrlData& pad);
};
