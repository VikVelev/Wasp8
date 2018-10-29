#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if _isWeb
const int isWeb = 1;
#include <emscripten/emscripten.h>
#else
const int isWeb = 0;
#include "./viewport/graphics.c"
#endif

int main(int argc, char ** argv) {

    const char* _isWeb = getenv("web");
    
    if(!isWeb) {
        printf("Standalone version.\n");
        initSDL();
        eventHandling_SDL();
    } else {
        printf("WASM Loaded, standing by.\n");
    }
    
}
