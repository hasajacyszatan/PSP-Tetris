#include "background.h"
#include <SDL_image.h>

Background::Background(SDL_Renderer* renderer, const char* background_path)
    : renderer(renderer), texture(nullptr), rect{}
{
    SDL_Surface* img = IMG_Load(background_path);
    if (img) {
        texture = SDL_CreateTextureFromSurface(renderer, img);
        rect    = {0, 0, img->w, img->h};
        SDL_FreeSurface(img);
    }
}

Background::~Background() {
    if (texture) SDL_DestroyTexture(texture);
}

int Background::draw() {
    if (texture)
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    return 0;
}
