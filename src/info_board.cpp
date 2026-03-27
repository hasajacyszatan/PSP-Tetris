#include "info_board.h"
#include "globals.h"
#include <SDL_ttf.h>
#include <string>

InfoBoard::InfoBoard(SDL_Renderer* renderer)
    : renderer(renderer)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, "NEXT:", white);
    nexttexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    nextrect = {20, 50, 0, 0};
    SDL_QueryTexture(nexttexture, NULL, NULL, &nextrect.w, &nextrect.h);

    surface = TTF_RenderUTF8_Blended(font, "HOLD:", white);
    holdertexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    holderrect = {20, 100, 0, 0};
    SDL_QueryTexture(holdertexture, NULL, NULL, &holderrect.w, &holderrect.h);
}

InfoBoard::~InfoBoard() {
    if (texture)       SDL_DestroyTexture(texture);
    if (leveltexture)  SDL_DestroyTexture(leveltexture);
    if (nexttexture)   SDL_DestroyTexture(nexttexture);
    if (holdertexture) SDL_DestroyTexture(holdertexture);
}

void InfoBoard::setScore(int s) {
    score = s;
    if (texture) { SDL_DestroyTexture(texture); texture = nullptr; }

    std::string text = "SCORE: " + std::to_string(score);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), white);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rect = {20, 20, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

void InfoBoard::setLevel(int l) {
    level = l;
    if (leveltexture) { SDL_DestroyTexture(leveltexture); leveltexture = nullptr; }

    std::string text = "LEVEL: " + std::to_string(level);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), white);
    leveltexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    levelrect = {20, 35, 0, 0};
    SDL_QueryTexture(leveltexture, NULL, NULL, &levelrect.w, &levelrect.h);
}

void InfoBoard::draw() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &backgroundRect);
    if (leveltexture)  SDL_RenderCopy(renderer, leveltexture,  NULL, &levelrect);
    if (texture)       SDL_RenderCopy(renderer, texture,       NULL, &rect);
    if (nexttexture)   SDL_RenderCopy(renderer, nexttexture,   NULL, &nextrect);
    if (holdertexture) SDL_RenderCopy(renderer, holdertexture, NULL, &holderrect);
}
