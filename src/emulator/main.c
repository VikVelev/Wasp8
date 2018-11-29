#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "cpu/cpu.c"
#include "utils/io.c"

#if _isWeb
const int isWeb = 1;
#include <emscripten/emscripten.h>
#else
const int isWeb = 0;
#include "./viewport/graphics.c"
#endif

const int REFRESH_RATE = 60;

int main(int argc, char ** argv) {

    const char* _isWeb = getenv("web");

    if(!isWeb) {
        printf("Standalone version.\n");
        init_SDL();
    } else {
        printf("WASM Loaded, standing by.\n");
    }

    chip8 Chip8;
    Chip8.log = debug_log;
    setup_input(&Chip8);
    
    // Initialize the Chip8 system and load the game into the memory  
    initialize(&Chip8);
    load_game(&Chip8, "/home/viktorv/Projects/Wasp8/TETRIS");
    

    Chip8.draw_flag = 0;
    Chip8.running = 1;
    // Emulation loop

    //Chip8.log(Chip8);
    while(Chip8.running) {
        
        // Emulate one cycle
        emulate_cycle(&Chip8);
        event_handling_SDL(&Chip8.running);

        // If the draw flag is set, update the screen
        // only two opcodes should set this flag: 0x00E0, 0xDXYN

        if(Chip8.draw_flag) {
            draw_graphics(&Chip8);
        }

        Chip8.draw_flag = 0;
        // Store key press state (Press and Release)
        check_keys(&Chip8);
        sleep(1.0/5);
    }
    
    printf("Closing...\n");

    return 0;
}