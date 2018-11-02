void __0x00E_op(chip8 *Chip8) {
    printf("hi\n");
}

const static struct {
    const char *opcode_name;
    void (*func) (chip8 *Chip8);
} opcode_map [] = {
    { "0x00E", __0x00E_op },
};