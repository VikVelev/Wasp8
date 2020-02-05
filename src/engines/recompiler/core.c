#include<stdio.h>

#ifndef CHIP8
#include "../../base/chip8.h"
#define CHIP8
#endif

#include "../../base/io/io.h"
#include "../../base/io/graphics.h"

const int REFRESH_RATE = 60;
chip8 Chip8;

int run_engine(int argc, char ** argv) {

    printf("Standalone Recompiler version.\n");
    init_SDL();

    Chip8.log = debug_log;
    Chip8.debug_screen = 0;
    Chip8.vintage_emulation = 1;

    setup_input(&Chip8);
    // Initialize the Chip8 system and load the game into the memory  
    initialize(&Chip8);
    load_game(&Chip8, argv[1]);
    
    long bg_color = 0x101b2d;
    long draw_color = 0xf4f4f4;

    Chip8.draw_flag = 0;
    Chip8.running = 1;
    int timer = 0;

    // Dispatcher Loop
    while(Chip8.running) {

        // // Emulate one cycle
        // emulate_cycle(&Chip8, &timer);
        printf("Doing nothing...\n");
        event_handling_SDL(&Chip8.running, &Chip8);

        // If the draw flag is set, update the screen
        // only two opcodes should set this flag: 0x00E0, 0xDXYN

        if(Chip8.draw_flag) {
        // draw_graphics(chip8 *Chip8, long bg_color, long draw_color, int (bool) invert colors, int (bool) swap colors)
            draw_graphics(&Chip8, bg_color, draw_color, 0, 0);
            Chip8.draw_flag = 0;
        }

        usleep(1000);
    }

    printf("Closing...\n");

    return 0;
}
