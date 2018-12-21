#include <SDL2/SDL.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static const int SCALING = 16;
static int WIDTH  = 64 * SCALING;
static int HEIGHT = 32 * SCALING;
static int BPP    = 32;

SDL_Surface* screen = NULL;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Event event;

void init_SDL() {

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("Failed to initialize SDL2.0\n");
    } else {
        SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
    }

}

void stop_SDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

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

void event_handling_SDL(unsigned short *running, chip8 *Chip8) {

    //EVENT HANDLING
    while (SDL_PollEvent(&event)) {

        if(event.type == SDL_KEYDOWN) {
            
            for (int i = 0; i < 16; i++) {
                if(event.key.keysym.scancode == key_map[i].scancode) {
                    //printf("DOWN %02X\n", key_map[i].hex_map);
                    Chip8->key[key_map[i].hex_map] = 1;
                }
            }

        }
        
        if(event.type == SDL_KEYUP) {

            for (int i = 0; i < 16; i++) {
                if(event.key.keysym.scancode == key_map[i].scancode) {
                    //printf("UP %02X\n", key_map[i].hex_map);
                    Chip8->key[key_map[i].hex_map] = 0;
                }
            }
        }

        if(event.type == SDL_QUIT) {
            *running = 0;
            stop_SDL();
        }
    }
}

int draw_graphics(chip8 *Chip8) {
    if(Chip8->opcode == 0x00) {

    }
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (Chip8->display[x + y * 64] == 1) {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            } else if (Chip8->display[x + y * 64] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
            SDL_RenderSetScale(renderer, SCALING, SCALING);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    SDL_RenderPresent(renderer);
    return 0;
}


