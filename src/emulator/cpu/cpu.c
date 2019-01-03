#include <string.h>
#ifndef CHIP8
#include "./cpu.h"
#define CHIP8
#endif
#include "./cpu_utils.c"

void initialize(chip8 *Chip8) {

    printf("Initializing\n");

    unsigned char fontset[80] = { 
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    Chip8->PC = 0x200; // Program counter starts at 0x200 (byte 0 - 512)
    // reset some values
    Chip8->opcode = 0;
    Chip8->I = 0;
    Chip8->sp = 0;

    Chip8->stack = createStack(16);
    // hacky way to set all array values to 0
    memset( Chip8->display, 0, sizeof Chip8->display );
    memset( Chip8->stack, 0, sizeof Chip8->stack );
    memset( Chip8->V, 0, sizeof Chip8->V );
    memset( Chip8->key, 0, sizeof Chip8->key );
    memset( Chip8->memory, 0, sizeof Chip8->memory );

    // load font
    for(int i = 0; i < 80; i++) {
        Chip8->memory[i] = fontset[i];
    }
    
    //reset timers
    Chip8->delay_timer = 0;
    Chip8->sound_timer = 0;
    
    Chip8->draw_flag = 1;
}

void emulate_cycle(chip8 *Chip8, int *timer) {
    fetch_opcode(Chip8);
    // Timer ticking happens on another thread
    decode_and_execute_opcode(Chip8);
    printf("%d\n", *timer);
}
