
void setup_input(chip8 *Chip8) {
    printf("Setting up input.\n");
}

int check_keys(chip8 **Chip8) {
    printf("Got input.\n");
    return 1;
}

void load_game(chip8 *Chip8, char * rom_dir) {

    printf("Loading %s\n", rom_dir);

    FILE *game = fopen(rom_dir, "r");

    //4096 (all memory) - 512 (from 0x000 to 0x200 - oem memory)
    unsigned char buffer[ 4096 - 512 ];
    fread(buffer, 4096 - 512, 1, game);

    fseek(game, 0, SEEK_END); 
    long buffer_size = ftell(game); //size in bytes
    fseek(game, 0, SEEK_SET);
    
    for(int i = 0; i < buffer_size; i++) {
        Chip8->memory[i + 512] = buffer[i];
    }

    printf("%d bytes loaded!\n", (int) buffer_size);
    
}