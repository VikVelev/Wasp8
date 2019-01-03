#include "opcodes.c"

void fetch_opcode(chip8 *Chip8) {
    //concatinating two bytes (each opcode is 2 bytes)
    Chip8->opcode = Chip8->memory[Chip8->PC] << 8 | Chip8->memory[Chip8->PC + 1];
}

void decode_and_execute_opcode(chip8 *Chip8) {
    //convert from hex to string and then search in the opcode_map and execute. (AWESOME)
    int opcode_map_length = sizeof(opcode_map) / sizeof(opcode_map[0]);
    
    for(int i = 0; i < opcode_map_length; i++) {
        if(opcode_map[i].suffices(Chip8->opcode)){
            printf("0x%04X: PC: %d, Executing opcode %s.\n", Chip8->opcode, Chip8->PC, opcode_map[i].opcode_name);
            opcode_map[i].exec(Chip8);
            break;
        } else if (i == opcode_map_length - 1) {
            printf("Unknown or not implemented opcode 0x%04X.\n", Chip8->opcode);

            Chip8->log(Chip8);
            Chip8->running = 0;
        }
    }
}

void update_timers(chip8 *Chip8) {
    if(Chip8->delay_timer > 0) {
        --Chip8->delay_timer;
    }

    if(Chip8->sound_timer > 0) {
        if(Chip8->sound_timer == 1) {
            //implement alsa or pulseaudio sound here
            printf("BEEP!\n");
        }
        --Chip8->sound_timer;
    }
}

void* Timer(chip8 *Chip8) {
    printf("Thread Spawned.\n");

    while(Chip8->running) {
        update_timers(Chip8);
        usleep(16666);
    }

    pthread_exit(NULL);

}
