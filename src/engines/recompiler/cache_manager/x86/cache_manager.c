#ifndef CHIP8
#include "../../../base/chip8.h"
#define CHIP8
#endif

void* get_x86_eip() {
    return get_x86_eip;
}

int setup_cache(chip8 *Chip8, state *cState) {

    return 1;
}

int exec_cache(chip8 *Chip8, state *cState) {

    return 1;
}


int execute_batch(chip8 *Chip8, state *cState, int *timer) {
    // if (g_hash_table_lookup(cState->caches, Chip8->memory[Chip8->PC])) {
        // execute the code
    // } else {
        // interpret, translate, emit the file into the cache table;
    // }

    return 1;
}