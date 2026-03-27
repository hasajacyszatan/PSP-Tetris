#include "falling_block.h"
#include <cstdlib>
#include <algorithm>

FallingBlock::FallingBlock(TetrisTable* table, SDL_Renderer* renderer)
    : renderer(renderer), table(table)
{
    tetro      = rand() % 7;
    tetromino  = &tetrominoes[tetro];
}

int FallingBlock::fall() {
    if (checkCollision(xposition, yposition + 1, tetromino->rotations[rotation])) {
        fillTable();
        movable = false;
        return 0;
    }
    yposition++;
    return 1;
}

int FallingBlock::drop() {
    while (fall() == 1) {}
    return 0;
}

void FallingBlock::rotate() {
    int next = (rotation + 1) % 4;
    if (!checkCollision(xposition, yposition, tetromino->rotations[next]))
        rotation = next;
}

int FallingBlock::left() {
    bool ok = true;
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (tetromino->rotations[rotation][y][x])
                if (xposition + x <= 0 || table->filledBlocks[yposition + y][xposition + x - 1])
                    ok = false;
    if (ok && movable) xposition--;
    return 0;
}

int FallingBlock::right() {
    bool ok = true;
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (tetromino->rotations[rotation][y][x])
                if (xposition + x + 1 >= 10 || table->filledBlocks[yposition + y][xposition + x + 1])
                    ok = false;
    if (ok && movable) xposition++;
    return 0;
}

int FallingBlock::draw() {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (tetromino->rotations[rotation][y][x])
                table->drawCellByCoordinates(x + xposition, y + yposition, tetromino->color);
    return 0;
}

bool FallingBlock::checkCollision(int posx, int posy, int current[4][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (!current[y][x]) continue;
            int ty = y + posy;
            int tx = x + posx;
            if (ty >= table->height || tx < 0 || tx >= 10) return true;
            if (table->filledBlocks[ty][tx])               return true;
        }
    }
    return false;
}

int FallingBlock::fillTable() {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (tetromino->rotations[rotation][y][x]) {
                table->filledBlocks[y + yposition][x + xposition] = tetro + 1;
                if (y + yposition <= 0)
                    state = STATE_GAMEOVER;
            }
        }
    }
    return 0;
}

void FallingBlock::drawGhost() {
    int ghostY = yposition;
    while (!checkCollision(xposition, ghostY + 1, tetromino->rotations[rotation]))
        ghostY++;
    if (ghostY == yposition) return;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (tetromino->rotations[rotation][y][x]) {
                SDL_Color c = tetromino->color;
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 90);
                int cx = table->xoffset + (x + xposition) * 12;
                int cy = table->yoffset + (y + ghostY)    * 12;
                SDL_Rect cell = {cx, cy, 10, 10};
                SDL_RenderFillRect(renderer, &cell);
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
            }
        }
    }
}

int switchblocks(FallingBlock* active, FallingBlock* hold) {
    std::swap(active->tetro, hold->tetro);
    active->tetromino = &tetrominoes[active->tetro];
    hold->tetromino   = &tetrominoes[hold->tetro];

    active->rotation  = 0;
    active->xposition = 3;
    active->yposition = 0;

    hold->xposition = 0;
    hold->yposition = 0;
    return 0;
}
