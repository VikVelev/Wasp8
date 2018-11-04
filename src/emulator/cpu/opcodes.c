#ifndef CHIP8
#include "cpu.h"
#define CHIP8
#endif

void __0x0NNN_op(chip8 *Chip8) {
    //Used to update the CMOS, who cares
    printf("I am a CMOS BEEP BOOP BUP\n");
    Chip8->log(Chip8);
    sleep(10);
    Chip8->PC += 2;
}

int __0x0NNN_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x0000 && opcode != 0x00E0 && opcode != 0x00EE);
}

//===========================================

void __0x00E0_op(chip8 *Chip8) {
    memset( Chip8->display, 0, sizeof Chip8->display );
    Chip8->PC += 2;
}

int __0x00E0_reqs(unsigned short opcode) {
    return (opcode == 0x00E0);
}

//===========================================

void __0x00EE_op(chip8 *Chip8) {
    Chip8->PC = Chip8->stack->top;
    --Chip8->sp;
}

int __0x00EE_reqs(unsigned short opcode) {
    return (opcode == 0x00EE);
}

//===========================================

void __0x1NNN_op(chip8 *Chip8) {
    Chip8->PC = Chip8->opcode & 0x0FFF;
}

int __0x1NNN_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x1000);
}

//===========================================

void __0x2NNN_op(chip8 *Chip8) {
    Chip8->sp++;
    push(Chip8->stack, Chip8->PC);
    Chip8->PC = Chip8->opcode & 0x0FFF;
}

int __0x2NNN_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x2000);
}

//===========================================

void __0x3XKK_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short KK = Chip8->opcode & 0x00FF;

    if(Chip8->V[X] == KK) {
        Chip8->PC += 2;
    }
}

int __0x3XKK_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x3000);
}

//===========================================

void __0x4XKK_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short KK = Chip8->opcode & 0x00FF;

    if(Chip8->V[X] != KK) {
        Chip8->PC += 2;
    }
}

int __0x4XKK_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x4000);
}

//===========================================

void __0x5XY0_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;

    if(Chip8->V[X] != Chip8->V[Y]) {
        Chip8->PC += 2;
    }
}

int __0x5XY0_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x5000);
}

//===========================================

void __0x6XKK_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short KK = Chip8->opcode & 0x00FF;

    Chip8->V[X] = KK;
    Chip8->PC += 2;
}

int __0x6XKK_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x6000);
}

//===========================================

void __0x7XKK_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short KK = Chip8->opcode & 0x00FF;

    Chip8->V[X] += KK;
    Chip8->PC += 2;
}

int __0x7XKK_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0x7000);
}

//===========================================

void __0x8XY0_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;

    Chip8->V[X] = Chip8->V[Y];
    Chip8->PC += 2;
}

int __0x8XY0_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8000);
}

//===========================================

void __0x8XY1_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;

    Chip8->V[X] = Chip8->V[X] | Chip8->V[Y];
    Chip8->PC += 2;
}

int __0x8XY1_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8001);
}

//===========================================

void __0x8XY2_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;

    Chip8->V[X] = Chip8->V[X] & Chip8->V[Y];
    Chip8->PC += 2;
}

int __0x8XY2_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8002);
}

//===========================================

void __0x8XY3_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;

    Chip8->V[X] = Chip8->V[X] ^ Chip8->V[Y];
    Chip8->PC += 2;
}

int __0x8XY3_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8003);
}

//===========================================

void __0x8XY4_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;

    if(Chip8->V[Y >> 4] > (0xFF - Chip8->V[X >> 8])) {
        Chip8->V[0xF] = 1; //carry
    } else {
        Chip8->V[0xF] = 0;
    }

    Chip8->V[X >> 8] += Chip8->V[Y >> 4];
    Chip8->PC += 2;  
}

int __0x8XY4_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8004);
}

//===========================================

void __0x8XY5_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;
    
    if(Chip8->V[X] > Chip8->V[Y]) {
        Chip8->V[0xF] = 1; //carry
    } else {
        Chip8->V[0xF] = 0;
    }

    Chip8->V[X] -= Chip8->V[Y];
    Chip8->PC += 2;  
}

int __0x8XY5_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8005);
}

//===========================================

void __0x8XY6_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;
    
    if((Chip8->V[X] & 0x01) == 1) {
        Chip8->V[0xF] = 1; //carry
    } else {
        Chip8->V[0xF] = 0;
    }

    Chip8->V[X] /= 2;
    Chip8->PC += 2;
}

int __0x8XY6_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8006);
}

//===========================================

void __0x8XY7_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;
    
    if(Chip8->V[Y] > Chip8->V[X]) {
        Chip8->V[0xF] = 1; //carry
    } else {
        Chip8->V[0xF] = 0;
    }

    Chip8->V[X] = Chip8->V[Y] - Chip8->V[X];
    Chip8->PC += 2;
}

int __0x8XY7_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x8007);
}

//===========================================

void __0x8XYE_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;
    
    if((Chip8->V[X] & 0x40) == 0b1000000) {
        Chip8->V[0xF] = 1; //carry
    } else {
        Chip8->V[0xF] = 0;
    }

    Chip8->V[X] *= 2;
    Chip8->PC += 2;
}

int __0x8XYE_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x800E);
}

//===========================================

void __0x9XY0_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short Y = Chip8->opcode & 0x00F0;

    if(Chip8->V[X] != Chip8->V[Y]) {
        Chip8->PC += 2;
    }
}

int __0x9XY0_reqs(unsigned short opcode) {
    return ((opcode & 0xF00F) == 0x9000);
}

//===========================================

void __0xANNN_op(chip8 *Chip8) {
    Chip8->I = Chip8->opcode & 0x0FFF;
    Chip8->PC += 2;
}

int __0xANNN_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0xA000);
}

//===========================================

void __0xBNNN_op(chip8 *Chip8) {
    Chip8->PC = ( Chip8->opcode & 0xFFF ) + Chip8->V[0];
}

int __0xBNNN_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0xB000);
}

//===========================================

void __0xCXKK_op(chip8 *Chip8) {
    unsigned short X = Chip8->opcode & 0x0F00;
    unsigned short KK = Chip8->opcode & 0x00FF;

    unsigned char random_byte = (unsigned char) (rand() % 255);
    Chip8->V[X] = random_byte & KK;
}

int __0xCXKK_reqs(unsigned short opcode) {
    return ((opcode & 0xF000) == 0xC000);
}

const static struct {

    const char *opcode_name;
    int (*suffices) (unsigned short opcode);
    void (*exec) (chip8 *Chip8);

} opcode_map [] = {
    { "0x00E0", __0x00E0_reqs ,__0x00E0_op },
    { "0x00EE", __0x00EE_reqs ,__0x00EE_op },
    { "0x0NNN", __0x0NNN_reqs, __0x0NNN_op },
    { "0x1NNN", __0x1NNN_reqs ,__0x1NNN_op },
    { "0x2NNN", __0x2NNN_reqs ,__0x2NNN_op },
    { "0x3XKK", __0x3XKK_reqs ,__0x3XKK_op },
    { "0x4XKK", __0x4XKK_reqs ,__0x4XKK_op },
    { "0x5XY0", __0x5XY0_reqs ,__0x5XY0_op },
    { "0x6XKK", __0x6XKK_reqs ,__0x6XKK_op },
    { "0x7XKK", __0x7XKK_reqs ,__0x7XKK_op },
    { "0x8XY0", __0x8XY0_reqs ,__0x8XY0_op },
    { "0x8XY1", __0x8XY1_reqs ,__0x8XY1_op },
    { "0x8XY2", __0x8XY2_reqs ,__0x8XY2_op },
    { "0x8XY3", __0x8XY3_reqs ,__0x8XY3_op },
    { "0x8XY4", __0x8XY4_reqs ,__0x8XY4_op },
    { "0x8XY5", __0x8XY5_reqs ,__0x8XY5_op },
    { "0x8XY6", __0x8XY6_reqs ,__0x8XY6_op },
    { "0x8XY7", __0x8XY7_reqs ,__0x8XY7_op },
    { "0x8XYE", __0x8XYE_reqs ,__0x8XYE_op },
    { "0x9XY0", __0x9XY0_reqs ,__0x9XY0_op },
    { "0xANNN", __0xANNN_reqs ,__0xANNN_op },
    { "0xBNNN", __0xBNNN_reqs ,__0xBNNN_op },
    { "0xCXKK", __0xCXKK_reqs ,__0xCXKK_op },
};