#include <glib.h>

int initialize_state(state *st) {
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

void write8(void* raw_code, char byte) {
    // Append the byte to the raw_code;
}

void write16(void* raw_code, short byte) {
    // Append the 2 bytes to the raw_code;
}

void write32(void* raw_code, int byte) {
    // Append the 4 bytes to the raw_code;
}

void initialize_cache(cache* c) {
    c->write8 = write8;
    c->write16 = write16;
    c->write32 = write32;
}