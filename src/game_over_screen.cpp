#include "game_over_screen.h"
#include "globals.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <pspkernel.h>

GameOverScreen::GameOverScreen(SDL_Renderer* renderer, Background* bg)
    : renderer(renderer), texture(nullptr), imageTexture(nullptr),
      rect{}, imgRect{}, bg(bg)
{
}

GameOverScreen::~GameOverScreen() {
    if (texture)      SDL_DestroyTexture(texture);
    if (imageTexture) SDL_DestroyTexture(imageTexture);
}

int GameOverScreen::render() {
    SDL_Color white = {255, 255, 255, 255};
    const char* msg =
        "                         GAME OVER\n"
        "     press start to return to menu press select to exit.";

    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, msg, white, 480);
    if (surface) {
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    if (texture) {
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        rect.x = (480 - rect.w) / 2;
        rect.y = (272 - rect.h) / 2;
    }

    if (!imageTexture) {
        SDL_Surface* img = IMG_Load("gameover.png");
        if (img) {
            imageTexture = SDL_CreateTextureFromSurface(renderer, img);
            // imgRect = {(480 - img->w) / 2, 90, img->w, img->h};
            imgRect = {320, 90, img->w, img->h};
            SDL_FreeSurface(img);
        }
    }
    return 0;
}

int GameOverScreen::draw(const SceCtrlData& pad) {
    if (pad.Buttons & PSP_CTRL_START)  state = STATE_MENU;
    if (pad.Buttons & PSP_CTRL_SELECT) sceKernelExitGame();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    bg->draw();

    SDL_RenderCopy(renderer, imageTexture, NULL, &imgRect);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    return 0;
}
