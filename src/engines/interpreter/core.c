#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#ifndef CHIP8
#include "../../base/chip8.h"
#define CHIP8
#endif

#include "../../base/io/io.h"
#include "../../base/io/graphics.h"

#include "./pipeline.c"

int run_engine(chip8 *Chip8, int argc, char ** argv) {

    printf("Standalone Interpreter version.\n");
    
    long bg_color = 0x101b2d;
    long draw_color = 0xf4f4f4;

    int timer = 0;
    // Chip8.log(Chip8);

    int thread_number = 1;
    pthread_t timer_thread;
    int code;

    printf("Spawning timer thread!\n");
    code = pthread_create(&timer_thread, NULL,(void *) Timer, Chip8);

    if(code) {
        printf("ERROR; return code from pthread_create() is %d\n", code);
        exit(-1);
    }
    // Emulation loop
    
    while(Chip8->running) {

        // Emulate one cycle
        emulate_cycle(Chip8, &timer);
        event_handling_SDL(&Chip8->running, Chip8);

        // If the draw flag is set, update the screen
        // only two opcodes should set this flag: 0x00E0, 0xDXYN

        if(Chip8->draw_flag) {
        // draw_graphics(chip8 *Chip8, long bg_color, long draw_color, int (bool) invert colors, int (bool) swap colors)
            draw_graphics(Chip8, bg_color, draw_color, 0, 0);
            Chip8->draw_flag = 0;
        }
        usleep(1000);

    }

    printf("Closing...\n");

    return 0;
}