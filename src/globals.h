#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

// ── Fonty (definicje w main.cpp) ──────────────────────────────────────────────
extern TTF_Font* font;
extern TTF_Font* bigfont;
extern TTF_Font* iconfont;

// ── Wynik ─────────────────────────────────────────────────────────────────────
extern int score;

// ── Stan gry ──────────────────────────────────────────────────────────────────
enum GameState {
    STATE_MENU,
    STATE_SETUP,
    STATE_GUIDE,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAMEOVER,
    STATE_EXIT,
    STATE_LEVEL_SELECT
};
extern GameState state;

// ── Ustawienia ────────────────────────────────────────────────────────────────
struct GameSettings {
    int  startlevel;
    bool musicenabled;
};
extern GameSettings settings;

// ── Tetromino ─────────────────────────────────────────────────────────────────
struct Tetromino {
    int rotations[4][4][4];
    SDL_Color color;
};

// tablica 7 tetrominoes — definicja w tetromino_data.cpp
extern Tetromino tetrominoes[7];
