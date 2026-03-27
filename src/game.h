#pragma once
#include <SDL.h>
#include <pspctrl.h>
#include "tetris_table.h"
#include "falling_block.h"
#include "background.h"
#include "info_board.h"

class Game {
private:
    SDL_Renderer* renderer;
    TetrisTable*  table;
    TetrisTable*  holder;
    TetrisTable*  next;
    Background*   background;
    InfoBoard*    info;
    FallingBlock* block;
    FallingBlock* holderblock;
    FallingBlock* nextblock;
    int pressed    = 0;
    int inputdelay = 0;

    int  getFramesPerDrop(int score);

public:
    bool switched = false;
    int  fall     = 0;
    int  granica  = 90;
    int  level    = 1;

    Game(SDL_Renderer* renderer);
    ~Game();

    void reset();
    void draw();
    void handleinput(const SceCtrlData& pad);
};
