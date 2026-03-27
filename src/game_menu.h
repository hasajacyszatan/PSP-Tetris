#pragma once
#include <SDL.h>
#include <pspctrl.h>
#include <vector>
#include <string>
#include <functional>
#include "background.h"

struct MenuOption {
    std::string           text;
    std::function<void()> action;
    bool                  editable = false;
};

class GameMenu {
private:
    SDL_Renderer*             renderer;
    Background*               background;
    std::vector<MenuOption>   menuoptions;

    std::vector<SDL_Texture*> texturesNormal;
    std::vector<SDL_Texture*> texturesSelected;
    SDL_Rect                  textRects[10]; // max 10 opcji

    int  menuindex = 0;
    bool clicked   = false;
    SDL_Rect bgrect = {480/2 - 100, 270/2 - 100, 200, 200};

    void generateTextures();

public:
    GameMenu(SDL_Renderer* renderer, Background* bg, std::vector<MenuOption>& mo);
    ~GameMenu();

    void refresh();
    void render();
    int  handleinput(const SceCtrlData& pad);
};
