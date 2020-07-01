#pragma once
#ifndef EMITTER_H
#include "../emitter/x86/emitter.h"
#endif

typedef struct {
    cache (*translate_next_batch) (chip8*, state*);
    void (*translate_refresh_call) (chip8*, emitter*);
    void (*execute_next_batch) (chip8*, state*);
} translator;

#include "translator.c"