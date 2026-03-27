#include "game.h"
#include "globals.h"
#include <cmath>

// ── Prędkości spadania (G/klatkę dla poziomów 0–15) ───────────────────────────
static const double gValues[] = {
    0.0,
    0.01667, 0.021017, 0.026977, 0.035256, 0.04693,
    0.06361, 0.0879,   0.1236,   0.1775,   0.2598,
    0.388,   0.59,     0.92,     1.46,     2.36
};

int Game::getFramesPerDrop(int score) {
    level = settings.startlevel;
    int currentGoal = 5;
    int tempScore   = score;
    while (tempScore >= currentGoal) {
        tempScore   -= currentGoal;
        level++;
        currentGoal  = 5 * level;
    }
    info->setLevel(level);
    if (level > 15) level = 15;
    return static_cast<int>(std::round(1.0 / gValues[level]));
}

Game::Game(SDL_Renderer* renderer)
    : renderer(renderer)
{
    table  = new TetrisTable(renderer);
    next   = new TetrisTable(renderer);
    holder = new TetrisTable(renderer);

    next->width   = 4;  next->xoffset  = 20; next->yoffset  = 70;  next->height  = 4;
    holder->width = 4;  holder->xoffset= 20; holder->yoffset= 120; holder->height= 4;

    background = new Background(renderer, "background.png");
    info       = new InfoBoard(renderer);
    info->setScore(0);
    info->setLevel(0);

    block       = new FallingBlock(table, renderer);
    holderblock = new FallingBlock(holder, renderer);
    nextblock   = new FallingBlock(next, renderer);

    holderblock->xposition = 0;
    nextblock->xposition   = 0;

    granica = getFramesPerDrop(score);
}

Game::~Game() {
    delete table;
    delete holder;
    delete next;
    delete background;
    delete info;
    delete block;
    delete holderblock;
    delete nextblock;
}

void Game::reset() {
    table->reset();
    info->setScore(0);
    info->setLevel(0);
    switched = false;
    fall     = 0;
    granica  = 90;
    level    = 0;

    delete block;
    block = new FallingBlock(table, renderer);

    delete holderblock;
    holderblock = new FallingBlock(holder, renderer);
    holderblock->xposition = 0;
}

void Game::draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    fall++;
    if (fall == granica) {
        granica = getFramesPerDrop(score);
        block->fall();
        fall = 0;
    }

    background->draw();
    table->drawTable();
    block->drawGhost();
    block->draw();
    info->draw();
    holderblock->draw();
    nextblock->draw();
}

void Game::handleinput(const SceCtrlData& pad) {
    inputdelay++;
    if (pad.Buttons) pressed++;
    else             pressed = 0;

    if (pressed == 1) {
        if (pad.Buttons & PSP_CTRL_RTRIGGER) {
            if (!switched) {
                switchblocks(block, holderblock);
                switched = true;
            }
        }
        if (pad.Buttons & PSP_CTRL_CROSS) block->rotate();
        if (pad.Buttons & PSP_CTRL_UP)    block->drop();
        if (pad.Buttons & PSP_CTRL_DOWN)  block->fall();
        if (pad.Buttons & PSP_CTRL_LEFT)  block->left();
        if (pad.Buttons & PSP_CTRL_RIGHT) block->right();
    }

    if (inputdelay == 4) {
        inputdelay = 0;
        if (pressed > 6) {
            if (pad.Buttons & PSP_CTRL_DOWN)  block->fall();
            if (pad.Buttons & PSP_CTRL_LEFT)  block->left();
            if (pad.Buttons & PSP_CTRL_RIGHT) block->right();
        }
        if (!block->movable) {
            switched = false;
            switchblocks(block, nextblock);
            block->movable = true;

            delete nextblock;
            nextblock = new FallingBlock(next, renderer);
            nextblock->xposition = 0;

            int lines = table->check();
            if (lines) info->setScore(score + lines);
        }
    }
}
