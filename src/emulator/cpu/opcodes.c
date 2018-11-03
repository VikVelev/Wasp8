#ifndef CHIP8
#include "cpu.h"
#define CHIP8
#endif

void __0x00E0_op(chip8 *Chip8) {
    memset( Chip8->display, 0, sizeof Chip8->display );
    Chip8->PC += 2;  
}

int __0x00E0_reqs(short opcode) {
    return ((opcode & 0x00F0) == 0x00E0);
}

//===========================================

void __0x00EE_op(chip8 *Chip8) {
    Chip8->PC = Chip8->stack->top;
    --Chip8->sp;
}

int __0x00EE_reqs(short opcode) {
    return ((opcode & 0x00FF) == 0x00EE);
}

//===========================================

void __0x1NNN_op(chip8 *Chip8) {
    Chip8->PC = Chip8->opcode & 0x0FFF;
}

int __0x1NNN_reqs(short opcode) {
    return ((opcode & 0xF000) == 0x1000);
}

//===========================================

void __0x2NNN_op(chip8 *Chip8) {
    Chip8->sp++;
    push(Chip8->stack, Chip8->PC);
    Chip8->PC = Chip8->opcode & 0x0FFF;
}

int __0x2NNN_reqs(short opcode) {
    return ((opcode & 0xF000) == 0x2000);
}

//===========================================

void __0x3XKK_op(chip8 *Chip8) {
    short X = Chip8->opcode & 0x0F00;
    short KK = Chip8->opcode & 0x00FF;

    if(Chip8->V[X] == KK) {
        Chip8->PC += 2;
    }
}

int __0x3XKK_reqs(short opcode) {
    return ((opcode & 0xF000) == 0x3000);
}

//===========================================

void __0x4XKK_op(chip8 *Chip8) {
    short X = Chip8->opcode & 0x0F00;
    short KK = Chip8->opcode & 0x00FF;

    if(Chip8->V[X] != KK) {
        Chip8->PC += 2;
    }
}

int __0x4XKK_reqs(short opcode) {
    return ((opcode & 0xF000) == 0x4000);
}

//===========================================

void __0xANNN_op(chip8 *Chip8) {
    Chip8->I = Chip8->opcode & 0x0FFF;
    Chip8->PC += 2;
}

int __0xANNN_reqs(short opcode) {
    return ((opcode & 0xF000) == 0xA000);
}

const static struct {

    const char *opcode_name;
    int (*suffices) (short opcode);
    void (*exec) (chip8 *Chip8);

} opcode_map [] = {
    { "0x00E0", __0x00E0_reqs ,__0x00E0_op },
    { "0x00EE", __0x00EE_reqs ,__0x00EE_op },
    { "0x1NNN", __0x1NNN_reqs ,__0x1NNN_op },
    { "0x2NNN", __0x2NNN_reqs ,__0x2NNN_op },
    { "0x3XKK", __0x3XKK_reqs ,__0x3XKK_op },
    { "0x4XKK", __0x4XKK_reqs ,__0x4XKK_op },
    { "0xANNN", __0xANNN_reqs ,__0xANNN_op },
};