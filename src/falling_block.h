#pragma once
#include <SDL.h>
#include "globals.h"
#include "tetris_table.h"

class FallingBlock {
private:
    SDL_Renderer* renderer;

public:
    bool movable     = true;
    unsigned char rotation = 0;
    unsigned char tetro;
    Tetromino*    tetromino;
    TetrisTable*  table;
    int xposition = 3;
    int yposition = 0;

    FallingBlock(TetrisTable* table, SDL_Renderer* renderer);

    int  fall();
    int  drop();
    void rotate();
    int  left();
    int  right();
    int  draw();
    bool checkCollision(int posx, int posy, int current[4][4]);
    int  fillTable();
    void drawGhost();
};

// Zamienia bloki aktywny ↔ trzymany
int switchblocks(FallingBlock* active, FallingBlock* hold);
