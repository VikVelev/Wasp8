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

void event_handling_SDL(unsigned short *running) {

    //EVENT HANDLING
    while (SDL_PollEvent(&event)) {

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


