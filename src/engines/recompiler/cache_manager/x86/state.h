#include <gmodule.h>
#ifndef STATE_H
#define STATE_H

typedef enum {
    NONE, 
    DYNAREC_EMIT,
    OUT_OF_CODE,
    USE_INTERPRETER, 
    SELF_MODIFYING_CODE,
    PREPARE_FOR_DIRECT_JUMP,
    PREPARE_FOR_INDIRECT_JUMP,
    PREPARE_FOR_STACK_JUMP,
    PREPARE_FOR_CONDITIONAL_JUMP
} Interrupt;

typedef struct {
    size_t x86_pc;   // where is the host
    void* raw_code;  // Will be set by the emitter
    short  c8_start; // where is the target
    short  c8_size;  // end = start + size
    // Abstract methods, they should modify and increment c8_size
    void (*write8)  (void*, char);
    void (*write16) (void*, short);
    void (*write32) (void*, int);
} cache;

typedef struct {
    void *x86_resume_address; 
    GHashTable *jump_table;
    GHashTable *caches;         // just lookup to see if the opcode is already cached 
    Interrupt interrupt;
} state;

#include "./init.c"
#include "./cache_manager.c"

#endif