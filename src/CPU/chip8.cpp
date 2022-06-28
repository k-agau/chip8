#include "../include/CPU/chip8.h"


chip8::chip8() {

}

void chip8::initialize(const char* name) {
    pc      = 0x200;         // Program counter starts @ 0x200
    opcode  = 0;             // Resets opcode
    I       = 0;             // Reset index register
    sp      = 0;             // Reset stack pointer

    // Clear display
    clearDisplay();
    // CLear stack
    clearStack();
    // Clear registers V0-VF
    clearRegisters();
    // Clear memory
    clearMemory();
    // Load fontset
    loadFont();
    // Load program

    char buffer[BUFFER_SIZE];
    FILE *game = loadGame(name);
    std::setbuf(game, buffer);
    loadProgram(buffer);
}

void chip8::emulateCycle() {
    opcode = memory[pc] << 8 | memory[pc + 0x1];

    switch(opcode & 0xF000) {
        case 0x1000:
            op3();
            break;
        case 0x3000:
            op5();
            break;
        case 0x4000:
            op6();
            break;
        case 0x0004:
            op14();
            break;
        case 0x0033:
            op32();
            break;
    }
    pc += 2;

    if(delay_timer > 0) {
        --delay_timer;
    }
    if(sound_timer > 0) {
        if(sound_timer == 1) {
            printf("BEEP!\n");
            --sound_timer;
        }
    }
    key[0]++;
}

void chip8::clearDisplay() {
    for(uint32_t i = 0; i < 64 * 32; ++i) gfx[i] = 0;
}

void chip8::clearStack() {
    for(uint32_t i = 0; i < 16; ++i) stack[i] = 0;
}

void chip8::clearRegisters() {
    for(uint32_t i = 0; i < 16; ++i) V[i] = 0;
}

void chip8::clearMemory() {
    for(uint32_t i = 0; i < 4096; ++i) memory[i] = 0;
}

void chip8::loadFont() {
    for(uint32_t i = 0; i < 80; ++i) {
        memory[i] = CHIP8_FONT_SET[i];
    }
}

std::FILE* chip8::loadGame(const char* name) {
    return std::fopen(name, "r");
}

void chip8::loadProgram(char buffer[]) {
    for(uint32_t i = 0; i < BUFFER_SIZE; ++i) {
        memory[i + pc] = buffer[i];
    }
}

bool chip8::getDrawFlag() {
    return drawFlag;
}

inline unsigned short chip8::xReg() {
    return (opcode & 0x0F00) >> 8;
}

inline unsigned short chip8::yReg() {
    return (opcode & 0x00F0) >> 4;
}

void chip8::op0() {
    pc = (opcode & 0x0FFF);
}

void chip8::op1() {
    clearDisplay();
}

void chip8::op2() {
    pc = stack[--sp];

}

void chip8::op3() {
    pc = (opcode & 0x0FFF);
}

void chip8::op4() {
    stack[sp] = pc;
    ++sp;
    pc = opcode & 0x0FFF;
}

void chip8::op5() {
    if(V[xReg()] == (opcode & 0x00FF)) {
        pc += 2; // ?
    }
}

void chip8::op6() {
    if(V[xReg()] != (opcode & 0x00FF)) {
        pc += 2; // ?
    }
}

void chip8::op7() {
    if(V[xReg()] == V[yReg()]) {
        pc += 2; // ?
    }
}

void chip8::op8() {
    V[xReg()] = (opcode & 0x00FF);
}

void chip8::op9() {
    V[xReg()] += (opcode & 0x00FF);
}

void chip8::op10() {
    V[xReg()] = V[yReg()];
}

void chip8::op11() {
    V[xReg()] |= V[yReg()];
}

void chip8::op12() {
    V[xReg()] &= V[yReg()];
}

void chip8::op13() {
    V[xReg()] ^= V[yReg()];
}

void chip8::op14() {
    if(V[yReg()] > (0xFF - V[xReg()])) {
        V[0xF] = 1; // Carry
    } else {
        V[0xF] = 0;
    }
    V[xReg()] += V[yReg()];
}

void chip8::op15() {
    if(V[yReg()] > (0xFF - V[xReg()])) {
        V[0xF] = 0;
    } else {
        V[0xF] = 1;
    }
    V[xReg()] -= V[yReg()];
}

void chip8::op16() {
    V[0xF] = V[xReg()] & 1;
    V[xReg()] >>= 1;
}

void chip8::op17() {
    if(V[xReg()] > (0xFF - V[yReg()])) {
        V[0xF] = 0;
    } else {
        V[0xF] = 1;
    }
    V[xReg()] = V[yReg()] - V[xReg()];
}

void chip8::op18() {
    V[0xF] = 1 << (unsigned char)(std::log2((V[xReg()])));
    V[xReg()] <<= 1;
}

void chip8::op19() {
    if(V[xReg()] != V[yReg()]) {
        pc += 2;
    }
}

void chip8::op20() {
    I = (opcode & 0x0FFF);
}

void chip8::op21() {
    pc = V[0x0] + (opcode & 0x0FFF);
}

void chip8::op22() {
    V[xReg()] = std::rand() & (opcode & 0x00FF);
}

void chip8::op23() {
    unsigned short xCord = V[xReg()], yCord = V[yReg()], height = (opcode & 0x000F);
    unsigned short pixel;

    for(unsigned short yLine = 0; yLine < height; ++ yLine) {
        pixel = memory[I + yLine];
        for(unsigned short xLine = 0; xLine < 8; ++ xLine) {
            if((pixel & (0x80 >> xLine)) != 0) {
                if(gfx[(xCord + xLine + ((yLine + yLine) * 64))] == 1) {
                    V[0xF] = 1;
                }
                gfx[xCord + xLine + ((yCord + yLine) * 64)] ^= 1;
            }
        }
    }
    drawFlag = true;
}

void chip8::op24() {

}

void chip8::op25() {

}

void chip8::op26() {
    V[xReg()] = delay_timer;
}

void chip8::op27() {

}

void chip8::op28() {
    delay_timer = V[xReg()];
}

void chip8::op29() {
    sound_timer = V[xReg()];
}

void chip8::op30() {
    I += V[xReg()];
}

void chip8::op31() {
    I = CHIP8_FONT_SET[V[xReg()]];
}

void chip8::op32() {
    memory[I]     = V[xReg()] / 100;
    memory[I + 1] = V[xReg()] / 10 % 10;
    memory[I + 2] = V[xReg()] % 100 % 10;
}

void chip8::op33() {
    for(unsigned short i = 0; i <= xReg(); ++i) {
        memory[I + i] = V[i];
    }
}

void chip8::op34() {
    for(unsigned short i = 0; i <= xReg(); ++i) {
        V[i] = memory[I + i];
    }
}