#ifndef STATE_H
#include "../cache_manager/x86/state.h"
#endif

cache translate_next_batch(chip8* Chip8, state* cState) {
    cache new_cache;
    initialize_cache(&new_cache);
    // Run through emitter until next jump
    return new_cache;
}

void translate_refresh_call(chip8* Chip8, emitter* emitter) {

}

void execute_next_batch(chip8* Chip8, state* cState) {

}

void initialize_translator(translator* t) {
    t->translate_next_batch = translate_next_batch;
    t->translate_refresh_call = translate_refresh_call;
    t->execute_next_batch = execute_next_batch;
}