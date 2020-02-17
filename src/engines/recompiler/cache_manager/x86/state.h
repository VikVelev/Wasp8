#include <gmodule.h>

typedef enum {
    NONE, 
    DYNAREC_EMIT, 
    OUT_OF_CODE, 
    USE_INTERPRETER, 
    SELF_MODIFYING_CODE,
    PREPARE_FOR_DIRECT_JUMP,
    PREPARE_FOR_INDIRECT_JUMP,
    PREPARE_FOR_STACK_JUMP,
    PREPARE_FOR_DIRECT_JUMP,
    PREPARE_FOR_CONDITIONAL_JUMP
} Interrupt;

typedef struct {
    size_t x86_pc;
    short  c8_start;
    short  c8_end;
} cache;

typedef struct {
    void *x86_resume_address;
    GHashTable *jump_table;
    GHashTable *caches;         // just lookup to see if the opcode is already cached 
    Interrupt interrupt;
} state;

#include "./init_state.c"
#include "./cache_manager.c"