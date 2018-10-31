#include <SDL/SDL.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static const int SCALING = 15;
static int WIDTH  = 64 * SCALING;
static int HEIGHT = 32 * SCALING;
static int BPP    = 32;
static char * error_screen_path = "";

SDL_Surface* screen = NULL;
SDL_Surface* error_screen = NULL;
SDL_Event event;

void init_SDL() {

    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_WM_SetCaption( "WASP8", NULL );

    //UPDATE SCREEN HERE
    screen = SDL_SetVideoMode( WIDTH, HEIGHT, BPP, SDL_SWSURFACE );
}

void stop_SDL() {

    SDL_FreeSurface( error_screen );
    SDL_Quit();

}

void event_handling_SDL(unsigned short *running) {

    error_screen = SDL_LoadBMP( error_screen_path );

    SDL_BlitSurface( error_screen, NULL, screen, NULL );
    SDL_Flip( screen );

    //EVENT HANDLING
    while (SDL_PollEvent(&event)) {

        if(event.type == SDL_QUIT) {
            *running = 0;
            stop_SDL();
        }
        //Handle events here
    }

}

int draw_graphics() {
    return 0;
}