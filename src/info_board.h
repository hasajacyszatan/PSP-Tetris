#pragma once
#include <SDL.h>

class InfoBoard {
private:
    SDL_Color     white = {0, 0, 0, 255};
    SDL_Texture*  texture      = nullptr;
    SDL_Texture*  leveltexture = nullptr;
    SDL_Texture*  holdertexture= nullptr;
    SDL_Texture*  nexttexture  = nullptr;
    SDL_Rect      rect;
    SDL_Rect      levelrect;
    SDL_Rect      holderrect;
    SDL_Rect      nextrect;
    SDL_Renderer* renderer;
    SDL_Rect      backgroundRect = {10, 10, 100, 150};

public:
    int level = 0;

    InfoBoard(SDL_Renderer* renderer);
    ~InfoBoard();

    void setScore(int s);
    void setLevel(int l);
    void draw();
};
