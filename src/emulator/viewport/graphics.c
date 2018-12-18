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
    {"W", 0x0, SDL_SCANCODE_W},
    {"A", 0x1, SDL_SCANCODE_A},
    {"S", 0x2, SDL_SCANCODE_S},
    {"D", 0x3, SDL_SCANCODE_D},
    {"Q", 0x4, SDL_SCANCODE_Q},
    {"E", 0x5, SDL_SCANCODE_E},
    {"1", 0x6, SDL_SCANCODE_1},
    {"C", 0x7, SDL_SCANCODE_C},
    {"X", 0x8, SDL_SCANCODE_X},
    {"Z", 0x9, SDL_SCANCODE_Z},
    {"5", 0xA, SDL_SCANCODE_G},
    {"6", 0xB, SDL_SCANCODE_H},
    {"7", 0xC, SDL_SCANCODE_Y},
    {"8", 0xD, SDL_SCANCODE_U},
    {"9", 0xE, SDL_SCANCODE_P},
    {"X", 0xF, SDL_SCANCODE_L},
};

void event_handling_SDL(unsigned short *running, chip8 *Chip8) {

    //EVENT HANDLING
    while (SDL_PollEvent(&event)) {

        if(event.type == SDL_KEYDOWN) {
            printf("KEY DOWN: Keycode: %s (%d) Scancode: %s (%d)\n", 
            SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.sym,
            SDL_GetScancodeName(event.key.keysym.scancode),
            event.key.keysym.scancode);
            
            for (int i = 0; i < 16; i++) {
                if(event.key.keysym.scancode == key_map[i].scancode) {
                    printf("WOHO000000 %02X\n", key_map[i].hex_map);
                    Chip8->key[key_map[i].hex_map] = 1;
                }
            }

        }
        
        if(event.type == SDL_KEYUP) {
            printf("KEY UP: Keycode: %s (%d) Scancode: %s (%d)\n", 
            SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.sym,
            SDL_GetScancodeName(event.key.keysym.scancode),
            event.key.keysym.scancode);

            for (int i = 0; i < 16; i++) {
                if(SDL_GetKeyName(event.key.keysym.sym) == key_map[i].key_code) {
                    Chip8->key[key_map[i].hex_map] = 0;
                }
            }
        }

        if(event.type == SDL_QUIT) {
            *running = 0;
            stop_SDL();
        }
        //Handle events here
    }

}

int draw_graphics(chip8 *Chip8) {
    
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (Chip8->display[x + y * 64] == 1) {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderSetScale(renderer, SCALING, SCALING);
                SDL_RenderDrawPoint(renderer, x, y);
            }

        }
    }

    SDL_RenderPresent(renderer);
    return 0;
}


