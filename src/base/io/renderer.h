#ifndef WASP8_RENDERER_H
#define WASP8_RENDERER_H

#include <SDL2/SDL.h>

#define GRID_W 64
#define GRID_H 32

// A way of putting the chip8 display on screen.
// submit() gets called whenever the draw flag is set and tick() on every
// loop iteration, so renderers that work in the background (pts4d) can
// show their frames whenever they are ready.
typedef struct {
    const char *name;
    int  (*init)(SDL_Renderer *sdl, int win_w, int win_h, unsigned fg_rgb, unsigned bg_rgb);
    void (*submit)(const unsigned char *display, unsigned fg_rgb, unsigned bg_rgb);
    void (*tick)(void);
    void (*shutdown)(void);
} wasp8_renderer;

#endif
