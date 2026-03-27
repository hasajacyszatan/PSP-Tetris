#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspuser.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>

#include "globals.h"
#include "tetris_table.h"
#include "falling_block.h"
#include "background.h"
#include "info_board.h"
#include "game.h"
#include "game_menu.h"
#include "level_selector.h"
#include "game_over_screen.h"


// ── Globale (deklaracje extern są w globals.h) ────────────────────────────────
TTF_Font*    font     = nullptr;
TTF_Font*    bigfont  = nullptr;
TTF_Font*    iconfont = nullptr;
int          score    = 1;
GameState    state    = STATE_MENU;
GameSettings settings = {};

// ── Callbacki PSP ─────────────────────────────────────────────────────────────
static int exit_callback(int /*arg1*/, int /*arg2*/, void* /*common*/) {
    sceKernelExitGame();
    return 0;
}

static int callback_thread(SceSize /*args*/, void* /*argp*/) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

static int setup_callbacks() {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0) sceKernelStartThread(thid, 0, 0);
    return thid;
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int /*argc*/, char* /*argv*/[]) {
    setup_callbacks();

    settings.musicenabled = true;
    settings.startlevel   = 1;
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    font     = TTF_OpenFont("font.ttf",    13);
    bigfont  = TTF_OpenFont("font.ttf",    14);
    iconfont = TTF_OpenFont("PSIcons.ttf", 20);

    SDL_Window* window = SDL_CreateWindow(
        "PSPTetris",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        480, 272, 0
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SceCtrlData pad;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    // ── Obiekty gry ───────────────────────────────────────────────────────────
    Background backgroundmenu(renderer, "menubackground.png");
    Game       game(renderer);

    // Główne menu
    std::vector<MenuOption> opcjemenu = {
        { "Start game", []() { state = STATE_PLAYING;  }, false },
        { "Options",    []() { state = STATE_SETUP;    }, false },
        { "Exit",       []() { sceKernelExitGame();    }, false },
    };
    GameMenu menu(renderer, &backgroundmenu, opcjemenu);

    // Menu ustawień
    std::vector<MenuOption> opcjeustawien;
    opcjeustawien.push_back({
        "toggle music on",
        [&opcjeustawien]() {
            if (settings.musicenabled) {
                settings.musicenabled     = false;
                opcjeustawien[0].text     = "toggle music off";
            } else {
                settings.musicenabled     = true;
                opcjeustawien[0].text     = "toggle music on";
            }
        },
        true
    });
    opcjeustawien.push_back({ "change starting level", []() { state = STATE_LEVEL_SELECT; }, false });
    opcjeustawien.push_back({ "back",                  []() { state = STATE_MENU;         }, false });
    GameMenu setup(renderer, &backgroundmenu, opcjeustawien);

    LevelSelector  levelselector(renderer, &backgroundmenu);
    GameOverScreen gameover(renderer, &backgroundmenu);
    gameover.render();

    // ── Audio ─────────────────────────────────────────────────────────────────
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    Mix_Music* ogg_file = Mix_LoadMUS("music.ogg");
    if (!ogg_file) return 1;
    Mix_PlayMusic(ogg_file, -1);

    // ── Pętla główna ──────────────────────────────────────────────────────────
    while (true) {
        sceCtrlReadBufferPositive(&pad, 1);

        switch (state) {
            case STATE_MENU:
                Mix_PauseMusic();
                menu.handleinput(pad);
                break;
            case STATE_PLAYING:
                if (settings.musicenabled) Mix_ResumeMusic();
                game.draw();
                game.handleinput(pad);
                break;
            case STATE_GAMEOVER:
                Mix_PauseMusic();
                game.reset();
                gameover.draw(pad);
                break;
            case STATE_SETUP:
                setup.handleinput(pad);
                break;
            case STATE_LEVEL_SELECT:
                levelselector.draw();
                levelselector.handleinput(pad);
                break;
            default:
                break;
        }

        SDL_RenderPresent(renderer);
        sceKernelDelayThread(16000); // ~60 FPS
    }

    // ── Sprzątanie (normalnie nieosiągalne na PSP) ────────────────────────────
    Mix_FreeMusic(ogg_file);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    TTF_CloseFont(bigfont);
    TTF_CloseFont(iconfont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
