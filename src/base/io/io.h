#include <SDL2/SDL.h>
#include "io.c"

const static struct {
    const char *key_code;
    const int hex_map;
    SDL_Scancode scancode;
} key_map [] = {
    {"Q", 0x1, SDL_SCANCODE_Q},
    {"W", 0x2, SDL_SCANCODE_W},
    {"E", 0x3, SDL_SCANCODE_E},
    {"A", 0x4, SDL_SCANCODE_A},
    {"S", 0x5, SDL_SCANCODE_S},
    {"D", 0x6, SDL_SCANCODE_D},
    {"Z", 0x7, SDL_SCANCODE_Z},
    {"X", 0x8, SDL_SCANCODE_X},
    {"C", 0x9, SDL_SCANCODE_C},
    {"Left Alt", 0x0, SDL_SCANCODE_LALT},
    {"Left Ctrl", 0xA, SDL_SCANCODE_LCTRL},
    {"Space", 0xB, SDL_SCANCODE_SPACE},
    {"R", 0xC, SDL_SCANCODE_R},
    {"F", 0xD, SDL_SCANCODE_F},
    {"V", 0xE, SDL_SCANCODE_V},
    {"G", 0xF, SDL_SCANCODE_G},
};