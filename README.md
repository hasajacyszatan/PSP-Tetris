# PSP Tetris
<img src="https://github.com/hasajacyszatan/PSP-Tetris/blob/main/screenshots/s1.png" width=200>
<img src="https://github.com/hasajacyszatan/PSP-Tetris/blob/main/screenshots/s2.png" width=200>
A Tetris clone for the Sony PlayStation Portable, written in C++ using the pspdev toolchain.

## Requirements

- [pspdev toolchain](https://github.com/pspdev/pspdev) (PSP cross-compiler + libraries)
- CMake 3.11+
- The following libraries (included with pspdev):
  - SDL2
  - SDL2_mixer
  - SDL2_ttf
  - SDL2_image
  - FreeType, HarfBuzz, libpng, libjpeg, zlib

## Building

```bash
git clone https://github.com/hasajacyszatan/PSP-Tetris.git
cd PSP-Tetris
mkdir build && cd build
psp-cmake ..
make
```

## Installation

Copy the `PSPTetris` folder (containing `EBOOT.PBP`) to your Memory Stick:

```
ms0:/PSP/GAME/PSPTetris/EBOOT.PBP
```

Then launch it from the PSP's Game menu under Memory Stick.

## Controls

| Button | Action |
|---|---|
| D-Pad Left / Right | Move piece |
| D-Pad Down | Soft drop |
| Cross (×) / D-Pad Up | Rotate clockwise |
| Square (□) | Hard drop |
| Circle (○) | Hold piece |
| Start | Pause |

## License

This project is released for personal and educational use. No official affiliation with The Tetris Company.