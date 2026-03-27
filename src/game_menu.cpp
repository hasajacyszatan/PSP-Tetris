#include "game_menu.h"
#include "globals.h"

void GameMenu::generateTextures() {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0,   0,   0,   255};

    for (int i = 0; i < (int)menuoptions.size(); i++) {
        SDL_Surface* surfN = TTF_RenderUTF8_Blended(bigfont, menuoptions[i].text.c_str(), white);
        SDL_Surface* surfS = TTF_RenderUTF8_Blended(bigfont, menuoptions[i].text.c_str(), black);

        texturesNormal.push_back(SDL_CreateTextureFromSurface(renderer, surfN));
        texturesSelected.push_back(SDL_CreateTextureFromSurface(renderer, surfS));

        textRects[i] = {(480 - surfN->w) / 2, 50 + i * 30, surfN->w, surfN->h};

        SDL_FreeSurface(surfN);
        SDL_FreeSurface(surfS);
    }
}

GameMenu::GameMenu(SDL_Renderer* renderer, Background* bg, std::vector<MenuOption>& mo)
    : renderer(renderer), background(bg), menuoptions(mo)
{
    generateTextures();
}

GameMenu::~GameMenu() {
    for (auto t : texturesNormal)   SDL_DestroyTexture(t);
    for (auto t : texturesSelected) SDL_DestroyTexture(t);
}

void GameMenu::refresh() {
    for (auto t : texturesNormal)   SDL_DestroyTexture(t);
    for (auto t : texturesSelected) SDL_DestroyTexture(t);
    texturesNormal.clear();
    texturesSelected.clear();
    generateTextures();
}

void GameMenu::render() {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(renderer);
    background->draw();

    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
    SDL_RenderFillRect(renderer, &bgrect);

    for (int i = 0; i < (int)menuoptions.size(); i++) {
        if (i == menuindex) {
            SDL_Rect highlight = textRects[i];
            highlight.x -= 5; highlight.y -= 2;
            highlight.w += 10; highlight.h += 4;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &highlight);
            SDL_RenderCopy(renderer, texturesSelected[i], NULL, &textRects[i]);
        } else {
            SDL_RenderCopy(renderer, texturesNormal[i], NULL, &textRects[i]);
        }
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

int GameMenu::handleinput(const SceCtrlData& pad) {
    int size = (int)menuoptions.size();

    if (!clicked && pad.Buttons) {
        clicked = true;
        if (pad.Buttons & PSP_CTRL_UP)
            menuindex = (menuindex <= 0) ? size - 1 : menuindex - 1;
        if (pad.Buttons & PSP_CTRL_DOWN)
            menuindex = (menuindex >= size - 1) ? 0 : menuindex + 1;
        if (pad.Buttons & PSP_CTRL_CROSS) {
            menuoptions[menuindex].action();
            refresh();
        }
        if (pad.Buttons & PSP_CTRL_START)
            state = STATE_PLAYING;
    } else if (!pad.Buttons) {
        clicked = false;
    }

    render();
    return 0;
}
