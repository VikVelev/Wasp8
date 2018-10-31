#include "./cpu.h"
#include "./cpu_utils.c"

void initialize(chip8 *Chip8) {
    //init chip8 registers and memory
}

void emulate_cycle(chip8 *Chip8) {
    fetch_opcode(Chip8);
    decode_opcode(Chip8);
    execute_opcode(Chip8);
    update_timers(Chip8);
}
