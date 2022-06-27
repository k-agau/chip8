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
            // goto addr NNN
    }

    delay_timer++;
    sound_timer++;
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

void chip8::op3(unsigned short op) {

}