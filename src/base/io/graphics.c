
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

    int bg_r = (bg_color & 0xFF0000) >> 16;
    int bg_g = (bg_color & 0x00FF00) >> 8;
    int bg_b = (bg_color & 0x0000FF);

    int drw_r = (draw_color & 0xFF0000) >> 16;
    int drw_g = (draw_color & 0x00FF00) >> 8;
    int drw_b = (draw_color & 0x0000FF);

    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (Chip8->display[x + y * 64] == 1) {
                SDL_SetRenderDrawColor(renderer, drw_r, drw_g, drw_b, 0xFF);
            } else if (Chip8->display[x + y * 64] == 0) {
                SDL_SetRenderDrawColor(renderer, bg_r, bg_g, bg_b, 0xFF);
            }
            SDL_RenderSetScale(renderer, SCALING, SCALING);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    SDL_RenderPresent(renderer);
    return 0;
}


