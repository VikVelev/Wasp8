#ifdef RECOMPILER
#include "./engines/recompiler/core.c"
#else
#include "./engines/interpreter/core.c"
#endif

chip8 Chip8;

int main(int argc, char ** argv) {
    // argv[1] is path_to_rom
    // ./wasp8 path_to_rom
    init_SDL();

    Chip8.log = debug_log;
    Chip8.debug_screen = 0;
    Chip8.vintage_emulation = 1;

    setup_input(&Chip8);
    // Initialize the Chip8 system and load the game into the memory  
    initialize(&Chip8);
    load_game(&Chip8, argv[1]);

    Chip8.draw_flag = 0;
    Chip8.running = 1;

    run_engine(&Chip8, argc, argv);
    return 0;
}