#include <SDL/SDL.h>

static int WIDTH  = 1920;
static int HEIGHT = 1080;
static int BPP    = 32;


void initSDL() {

    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_WM_SetCaption( "WASP8", NULL );

    SDL_Surface* screen = NULL;
    SDL_Surface* error_screen = NULL;
    SDL_Event event;

    //UPDATE SCREEN HERE
    screen = SDL_SetVideoMode( WIDTH, HEIGHT, BPP, SDL_SWSURFACE );
    error_screen = SDL_LoadBMP( "../error.bmp" );

    SDL_BlitSurface( error_screen, NULL, screen, NULL );

    //FINISH UPDATING
    SDL_Flip( screen );

    int running = 1;

    //EVENT HANDLING
    while(running) {
        while (SDL_PollEvent(&event)) {

            if(event.type == SDL_QUIT) {
                running = 0;
            }

            //Handle events here
        }
    }

    SDL_FreeSurface( error_screen );

    //Quit SDL
    SDL_Quit();
}