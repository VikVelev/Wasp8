// The classic flat look. Instead of drawing every pixel as a point
// we fill a 64x32 texture and let SDL scale it up to the window.

static SDL_Renderer *flat_sdl = NULL;
static SDL_Texture  *flat_tex = NULL;

static int flat_init(SDL_Renderer *sdl, int win_w, int win_h, unsigned fg_rgb, unsigned bg_rgb) {
    (void)win_w; (void)win_h; (void)fg_rgb; (void)bg_rgb;

    flat_sdl = sdl;
    flat_tex = SDL_CreateTexture(sdl, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, GRID_W, GRID_H);

    if (!flat_tex) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

static void flat_submit(const unsigned char *display, unsigned fg_rgb, unsigned bg_rgb) {
    Uint32 pixels[GRID_W * GRID_H];
    Uint32 fg = 0xFF000000 | fg_rgb;
    Uint32 bg = 0xFF000000 | bg_rgb;

    for (int i = 0; i < GRID_W * GRID_H; i++) {
        pixels[i] = display[i] ? fg : bg;
    }

    SDL_UpdateTexture(flat_tex, NULL, pixels, GRID_W * sizeof(Uint32));
    SDL_RenderClear(flat_sdl);
    SDL_RenderCopy(flat_sdl, flat_tex, NULL, NULL);
    SDL_RenderPresent(flat_sdl);
}

static void flat_tick(void) {
    // Everything happens in submit
}

static void flat_shutdown(void) {
    if (flat_tex) {
        SDL_DestroyTexture(flat_tex);
    }
    flat_tex = NULL;
}

static const wasp8_renderer flat_renderer = {
    "flat", flat_init, flat_submit, flat_tick, flat_shutdown,
};
