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
    unsigned char display[64 * 32]; // DISPLAY ARRAY (Holding value 1 or 0)

    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned short stack[16]; // Stack to remember current opcode, so the program can jump to a certain address at any time. 
    unsigned short sp; // Stack pointer

    unsigned char key[16]; // Chip8 has HEX based keyboard.

    unsigned short drawFlag;
    unsigned short running;

} chip8;
