#include "tetris_table.h"
#include <SDL_image.h>

TetrisTable::TetrisTable(SDL_Renderer* renderer)
    : renderer(renderer)
{
    // Oryginał ładował tu gameover.png — przeniesione do GameOverScreen
}

void TetrisTable::reset() {
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            filledBlocks[y][x] = 0;
}

int TetrisTable::drawTableCell() {
    SDL_RenderFillRect(renderer, &block);
    return 0;
}

int TetrisTable::drawTable() {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
    SDL_Rect bg = {
        xoffset - 5,
        yoffset - 5,
        width  * 12 + 10,
        height * 12 + 10
    };
    SDL_RenderFillRect(renderer, &bg);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    int startY = yoffset;
    for (int y = 0; y < height; y++) {
        block.x = xoffset;
        block.y = startY + y * 12;
        for (int x = 0; x < width; x++) {
            int color = filledBlocks[y][x];
            if (color) {
                SDL_Color c = tetrominoes[color - 1].color;
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
            } else {
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            }
            drawTableCell();
            block.x += 12;
        }
    }
    return 0;
}

int TetrisTable::check() {
    int cleanedlines = 0;
    for (int y = 0; y < height; y++) {
        int filledCells = 0;
        for (int x = 0; x < width; x++)
            if (filledBlocks[y][x]) filledCells++;

        if (filledCells == width) {
            cleanedlines++;
            for (int row = y; row > 0; row--)
                for (int x = 0; x < width; x++)
                    filledBlocks[row][x] = filledBlocks[row - 1][x];
            for (int x = 0; x < width; x++)
                filledBlocks[0][x] = 0;
        }
    }
    return cleanedlines;
}

int TetrisTable::drawCellByCoordinates(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    block.x = xoffset + x * 12;
    block.y = yoffset + y * 12;
    drawTableCell();
    return 0;
}
