#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cpu/cpu.c"
#include "utils/io.c"

#if _isWeb
const int isWeb = 1;
#include <emscripten/emscripten.h>
#else
const int isWeb = 0;
#include "./viewport/graphics.c"
#endif

int main(int argc, char ** argv) {

    const char* _isWeb = getenv("web");
    int running = 1;

    if(!isWeb) {
        printf("Standalone version.\n");
        initSDL();
    } else {
        printf("WASM Loaded, standing by.\n");
    }

    chip8 myChip8;
    
    setupInput();
    
    // Initialize the Chip8 system and load the game into the memory  
    initialize();
    loadGame("pong");
    
    myChip8.drawFlag = 0;
    // Emulation loop
    while(running) {
        
        // Emulate one cycle
        emulateCycle(&myChip8.drawFlag);
        eventHandling_SDL(&running);

        // If the draw flag is set, update the screen
        if(myChip8.drawFlag) {
            drawGraphics();
        }

        // Store key press state (Press and Release)
        checkKeys();
    }
    
    printf("Closing...\n");

    return 0;
    
}