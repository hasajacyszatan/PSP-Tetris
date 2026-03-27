cmake_minimum_required(VERSION 3.11)

project(PSPTetris)
set(SOURCES
    src/main.cpp
    src/tetromino_data.cpp
    src/tetris_table.cpp
    src/falling_block.cpp
    src/background.cpp
    src/info_board.cpp
    src/game.cpp
    src/game_menu.cpp
    src/level_selector.cpp
    src/game_over_screen.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    # pspkernel
    pspctrl
    SDL2_ttf
    freetype
    png
    z
    m
    SDL2_image
    bz2
    harfbuzz
    jpeg
    pspdebug
    pspgum 
    intrafont
)

if(PSP)
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()
