#include "level_selector.h"
#include "globals.h"
#include <string>

LevelSelector::LevelSelector(SDL_Renderer* renderer, Background* bg)
    : renderer(renderer), bg(bg)
{
    rect  = {240 - 230/2, 136 - 60/2, 230, 45};
    rect2 = {10, 10, 230, 45};
}

void LevelSelector::draw() {
    running++;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    bg->draw();

    SDL_Color white = {255, 255, 255, 255};

    // Aktualny poziom
    std::string text    = "Current level: " + std::to_string(currentLevel);
    SDL_Surface* surf   = TTF_RenderUTF8_Blended(font, text.c_str(), white);
    SDL_Texture* tex    = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    if (tex) { SDL_RenderCopy(renderer, tex, NULL, &rect); SDL_DestroyTexture(tex); }

    // Ikona przycisku X
    SDL_Surface* iconSurf = TTF_RenderUTF8_Blended(iconfont, "X", white);
    SDL_Texture* iconTex  = SDL_CreateTextureFromSurface(renderer, iconSurf);
    SDL_Rect iconRect     = {10, 272 - 30, 30, 30};
    SDL_FreeSurface(iconSurf);
    if (iconTex) { SDL_RenderCopy(renderer, iconTex, NULL, &iconRect); SDL_DestroyTexture(iconTex); }

    // Tekst "- OK"
    SDL_Surface* okSurf = TTF_RenderUTF8_Blended(font, " - OK", white);
    SDL_Texture* okTex  = SDL_CreateTextureFromSurface(renderer, okSurf);
    SDL_Rect okRect     = {iconRect.x + iconRect.w, 10, 100, 30};
    SDL_FreeSurface(okSurf);
    if (okTex) { SDL_RenderCopy(renderer, okTex, NULL, &okRect); SDL_DestroyTexture(okTex); }
}

void LevelSelector::handleinput(const SceCtrlData& pad) {
    if (pad.Buttons && !clicked && running > 50) {
        clicked = true;
        if (pad.Buttons & PSP_CTRL_UP)    currentLevel++;
        if (pad.Buttons & PSP_CTRL_DOWN)  currentLevel--;
        if (pad.Buttons & PSP_CTRL_CROSS) {
            settings.startlevel = currentLevel;
            state = STATE_MENU;
        }
    } else if (!pad.Buttons) {
        clicked = false;
    }
}
