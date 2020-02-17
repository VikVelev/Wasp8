#include<stdio.h>

#ifndef CHIP8
#include "../../base/chip8.h"
#define CHIP8
#endif

#include "../../base/io/io.h"
#include "../../base/io/graphics.h"

#include "./cache_manager/x86/state.h"


int run_engine(chip8 *Chip8, int argc, char ** argv) {

    printf("Standalone Recompiler version.\n");
    
    long bg_color = 0x101b2d;
    long draw_color = 0xf4f4f4;
    int timer = 0;
    
    // state holds jump table and cached translated code.
    state cState;
    init_state(&cState);

    // Dispatcher Loop
    while(Chip8->running) {

        // Execute a batch of opcodes (could already be compiled or not) 
        // (batch could be with size 1 or more, depending on the cache and the followin opcodes)
        execute_batch(Chip8, &State, &timer);
        event_handling_SDL(&Chip8->running, Chip8);

        // If the draw flag is set, update the screen
        // only two opcodes should set this flag: 0x00E0, 0xDXYN
        if(Chip8->draw_flag) {
            // draw_graphics (
            //      chip8 *Chip8,
            //      long bg_color,
            //      long draw_color,
            //      int (bool) invert colors,
            //      int (bool) swap colors
            // )
            draw_graphics(Chip8, bg_color, draw_color, 0, 0);
            Chip8->draw_flag = 0;
        }

        usleep(10000);
    }

    printf("Closing...\n");

    return 0;
}
