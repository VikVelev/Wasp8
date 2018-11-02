void __0x00E_op(chip8 *Chip8) {
    printf("hi\n");
}

int __0x00E_reqs(char *name) {
    return 1;
}

const static struct {
    const char *opcode_name;
    int (*suffices) (char *opcode_string);
    void (*func) (chip8 *Chip8);
} opcode_map [] = {
    { "0x00E", __0x00E_reqs ,__0x00E_op },
};