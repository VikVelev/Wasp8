#include "./engines/interpreter/core.c"

int main(int argc, char ** argv) {
    // argv[1] is path_to_rom
    // ./wasp8 path_to_rom
    run_engine(argc, argv);
    return 0;
}