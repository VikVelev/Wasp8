#include "./renderer.h"
#include "./renderer_flat.c"
#include "./renderer_pts4d.c"

SDL_Surface* screen = NULL;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;
SDL_Event event;

static const unsigned DEFAULT_BG_COLOR = 0x101b2d;
static const unsigned DEFAULT_DRAW_COLOR = 0xf4f4f4;

static const wasp8_renderer *active_renderer = NULL;

// Uses pts4d if it was compiled in, unless WASP8_RENDERER=flat.
// Falls back to flat if pts4d fails to start.
void select_renderer() {
    const char *wanted = getenv("WASP8_RENDERER");
    const wasp8_renderer *renderers[2];
    int count = 0;

#ifdef WASP8_PTS4D
    if (!wanted || strcmp(wanted, "flat") != 0) {
        renderers[count++] = &pts4d_renderer;
    }
#else
    if (wanted && strcmp(wanted, "pts4d") == 0) {
        printf("Not built with PTS4D (make RENDERER=pts4d), using flat.\n");
    }
#endif
    renderers[count++] = &flat_renderer;

    for (int i = 0; i < count; i++) {
        if (renderers[i]->init(renderer, WIDTH, HEIGHT, DEFAULT_DRAW_COLOR, DEFAULT_BG_COLOR) == 0) {
            active_renderer = renderers[i];
            printf("Using the %s renderer.\n", active_renderer->name);
            return;
        }
        printf("Failed to start the %s renderer.\n", renderers[i]->name);
    }
}

void init_SDL() {
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("Failed to initialize SDL2.0\n");
    } else {
        SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        select_renderer();
    }
}

void stop_SDL() {
    if (active_renderer) {
        active_renderer->shutdown();
        active_renderer = NULL;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

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
            return;
        }
    }
}

// Called on every loop iteration so pts4d can show frames as they come in
void present_tick() {
    if (active_renderer) {
        active_renderer->tick();
    }
}

int draw_graphics(chip8 *Chip8, long bg_color, long draw_color, int invert, int swap) {

    if(invert) {
        bg_color = 0xffffff - bg_color;
        draw_color = 0xffffff - draw_color;
    }

    if(swap) {
        long temp_bg_color = bg_color;
        bg_color = draw_color;
        draw_color = temp_bg_color;
    }

    if (active_renderer) {
        active_renderer->submit(Chip8->display,
                                (unsigned)(draw_color & 0xFFFFFF),
                                (unsigned)(bg_color & 0xFFFFFF));
    }
    return 0;
}
