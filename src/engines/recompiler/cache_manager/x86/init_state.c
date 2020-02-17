#include <glib.h>

int init_state(state *st) {
    st->jump_table = g_hash_table_new(g_str_hash, g_str_equal);
    st->caches = g_hash_table_new(g_int64_hash, g_int64_equal);

    return 1;
}

int destroy_state(state *st) {
    g_hash_table_destroy(st->jump_table);
    g_hash_table_destroy(st->caches);
    // if needed free(something) here;

    return 1;
}
