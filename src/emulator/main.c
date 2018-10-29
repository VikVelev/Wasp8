#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if _isWeb
#include <emscripten/emscripten.h>
#else
const int isWeb = 0;
#include "./viewport/graphics.c"
#endif

int main(int argc, char ** argv) {

    const char* _isWeb = getenv("web");
    printf("WASM Loaded, standing by.\n");
    
    if(isWeb == 0) {
        initSDL();
    }
    
}
