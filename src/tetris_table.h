#pragma once
#include <SDL.h>
#include "globals.h"

class TetrisTable {
private:
    SDL_Renderer* renderer;

public:
    SDL_Rect block = {0, 0, 10, 10};
    int width    = 10;
    int height   = 20;
    int yoffset  = 10;
    int xoffset  = 185;
    int filledBlocks[20][10] = {};

    TetrisTable(SDL_Renderer* renderer);

    void reset();
    int  drawTable();
    int  check();
    int  drawCellByCoordinates(int x, int y, SDL_Color color);

private:
    int drawTableCell();
};
