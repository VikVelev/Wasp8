#include <SDL/SDL.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static int WIDTH  = 1920;
static int HEIGHT = 1080;
static int BPP    = 32;
static char * error_screen_path = "/home/viktorv/Projects/Wasp8/src/emulator/viewport/error.bmp";

SDL_Surface* screen = NULL;
SDL_Surface* error_screen = NULL;
SDL_Event event;

void initSDL() {

    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_WM_SetCaption( "WASP8", NULL );

    //UPDATE SCREEN HERE
    screen = SDL_SetVideoMode( WIDTH, HEIGHT, BPP, SDL_SWSURFACE );
}

void stop_SDL() {

    SDL_FreeSurface( error_screen );
    SDL_Quit();

}

void eventHandling_SDL() {

    error_screen = SDL_LoadBMP( error_screen_path );

    SDL_BlitSurface( error_screen, NULL, screen, NULL );
    SDL_Flip( screen );

    int running = 1;

    //EVENT HANDLING
    while(running) {
        while (SDL_PollEvent(&event)) {

            if(event.type == SDL_QUIT) {
                running = 0;
                stop_SDL();
            }

            //Handle events here
        }
    }
}

