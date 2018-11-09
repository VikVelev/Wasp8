#include <SDL2/SDL.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static const int SCALING = 16;
static int WIDTH  = 64 * SCALING;
static int HEIGHT = 32 * SCALING;
static int BPP    = 32;
static char * error_screen_path = "";

SDL_Surface* screen = NULL;
SDL_Surface* error_screen = NULL;

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

    SDL_FreeSurface( error_screen );
    SDL_Quit();

}

void event_handling_SDL(unsigned short *running) {

    error_screen = SDL_LoadBMP( error_screen_path );

    SDL_BlitSurface( error_screen, NULL, screen, NULL );

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
    Uint8 *pixels = (Uint8*) screen->pixels;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (Chip8->display[y + x] == 1) {
                for (int scaling = -SCALING/4; scaling <= SCALING/4; scaling++) {

                    if ( x <= -scaling) {
                        scaling = (scaling < 0) ? -x : x;
                    }

                    if ( y <= -scaling ) {
                        scaling = (scaling < 0) ? -y : y;
                    }
                    
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }

        }
    }

    SDL_RenderPresent(renderer);
    return 0;
}


