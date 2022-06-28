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

    delay_timer++;
    sound_timer++;
    key[0]++;
    pc += 2;


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
        memory[i] = chip8_fontset[i];
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

void chip8::op14() {
    if(V[yReg()] > (0xFF - V[xReg()])) {
        V[0xF] = 1; // Carry
    } else {
        V[0xF] = 0;
    }
    V[xReg()] += V[yReg()];
}

void chip8::op32() {
    memory[I] =     V[xReg()] / 100;
    memory[I + 1] = V[xReg()] / 10 % 10;
    memory[I + 2] = V[xReg()] % 100 % 10;
}