#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if isWeb
#include <emscripten/emscripten.h>
#else
#include "./viewport/graphics.c"
#endif

int main(int argc, char ** argv) {

    const char* isWeb = getenv("web");
    printf("WASM Loaded, standing by.\n");
    initSDL();
    
}
