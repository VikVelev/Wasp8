#include <gmodule.h>

typedef struct {
    GHashTable *jump_table;
    GHashTable *caches;             // array of pointers to memory addresses where the caches are located.
} state;

#include "./init_state.c"
#include "./cache_manager.c"