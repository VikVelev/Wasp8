#include "./utils/stack.h"
#include "string.h"

typedef struct {
    // stores the current opcode (every chip8 opcode is 2 bytes) (short is 2 bytes)
    
    unsigned short opcode;
    unsigned char memory[4096];
    /*
    The Chip 8 has 15 8-bit general purpose registers named V0,V1 up to VE. 
    The 16th register is used  for the ‘carry flag’. Eight bits is one byte 
    so we can use an unsigned char for this purpose:
    */
    unsigned char V[16];
    unsigned short I;  //index register
    unsigned short PC; //program counter, specifies opcode location from memory
    /*
    0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
    0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
    0x200-0xFFF - Program ROM and work RAM
    */
    unsigned char display[64*32]; // [X][Y] DISPLAY ARRAY (Holding value 1 or 0)

    unsigned char delay_timer;
    unsigned char sound_timer;

    Stack* stack; // Stack to remember current opcode, so the program can jump to a certain address at any time. 
    unsigned short sp; // Stack pointer

    unsigned char key[16]; // Chip8 has HEX based keyboard.

    unsigned short draw_flag; //0 or 1
    unsigned short running;  //0 or 1
    Stack* history;

    int debug_screen; //0 or 1
    int vintage_emulation; //0 or 1
    void (*log) ();
} chip8;

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
    memset( Chip8->display, 0, sizeof(Chip8->display));
    memset( Chip8->V, 0, sizeof(Chip8->V));
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

void debug_log(chip8 *Chip8) {
    printf("DEBUG LOG\n");
    printf("==============================\n");
    printf("Chip8 running: %s\n", Chip8->running ? "true" : "false");
    printf("\n");
    printf("Currently executing instruction: 0x%04X\n", Chip8->opcode);
    printf("\n");
    printf("Chip8 Draw flag: 0x%04X\n", Chip8->draw_flag);
    printf("\n");

    printf("==============================\n");
    printf("==========V registers=========\n");

    for(int i = 0; i < 16; i++) {
        printf("V[%02d]: 0x%02X\n", i, Chip8->V[i]);
    }

    printf("\n");
    
    printf("==========   Keys   =========\n");
    for(int i = 0; i < 16; i++) {
        printf("Key[%02d]: 0x%02X\n", i+1, Chip8->key[i]);
    }
    
    printf("\n");

    printf("==========I register=========\n");
    printf("I: 0x%04X\n", Chip8->I);

    printf("\n");

    printf("=======Program Counter=======\n");
    printf("PC: %d\n", Chip8->PC);

    printf("\n");
    printf("Stack pointer : 0x%04X\n", Chip8->sp);
    printf("\n");
    printf("=======Stack trace===========\n");
    
    for(int i = 0; i < 16; i++) {
        printf("%d : 0x%04X\n", i+1, Chip8->stack->array[i]);
    }
    
    printf("\n");
    
    printf("============Timers===========\n");
    printf("Delay Timer: 0x%02X\n", Chip8->delay_timer);
    printf("Sound Timer: 0x%02X\n", Chip8->sound_timer);
    
    if(Chip8->debug_screen) {
        printf("\n");
        printf("============DISPLAY===========\n");

        for (int i = 0; i < 32; i++) {
            char row[128] = "";
            for (int j = 0; j < 64; j++) {
                strcat(row, (Chip8->display[(j)+(i)*64] == 1)? "O " : "_ ");
            }
            printf("%s\n", row);
        }
    }
}
