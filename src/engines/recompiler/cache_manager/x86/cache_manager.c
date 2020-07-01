#ifndef CHIP8
#include "../../../base/chip8.h"
#define CHIP8
#endif

void* get_x86_eip() {
    // Nasty hack to get the instruction pointer
    return get_x86_eip;
}

int cache_setup(chip8 *Chip8, state *cState, cache *Cache) {
    // TODO
    return 1;
}

int cache_insert(chip8 *Chip8, state *cState, cache *Cache) {
    // TODO
    return 1;
}

int cache_exec(chip8 *Chip8, state *cState, cache *Cache) {
    // TODO
    return 1;
}


int cache_exec_batch(chip8 *Chip8, state *cState, cache *Cache, int *timer) {
    // TODO
    return 1;
}