#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

const unsigned char chip8_fontset[80] =
{
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
const uint32_t BUFFER_SIZE = 512;

class chip8 {
private:
    // To store the current opcode
    unsigned short opcode;
    // Emulates 4K memory
    unsigned char memory[4096];
    // 15 8-bit registers from V0 to VE
    unsigned char V[16];
    // Index register
    unsigned short I;
    // Program counter
    unsigned short pc;
    // For graphics
    unsigned char gfx[64 * 32];
    // Timer
    unsigned char delay_timer;
    // Timer
    unsigned char sound_timer;
    // Stack for subprograms
    unsigned short stack[16];
    // Stack pointer
    unsigned short sp;
    // Hex-based keypad
    unsigned char key[16];
    // True if should update graphics. False otherwise
    bool drawFlag;
    // Helper functions
    void clearDisplay();
    void clearStack();
    void clearRegisters();
    void clearMemory();
    void loadFont();
    void loadProgram(char buffer[]);
    std::FILE* loadGame(const char* name);
    inline unsigned short xReg();
    inline unsigned short yReg();
    // Functions
    // 0NNN
    void op0();

    // 00E0
    void op1();

    // 00EE
    void op2();

    // 1NNN
    void op3();

    // 2NNN
    void op4();

    // 3XNN
    void op5();

    // 4XNN
    void op6();

    // 5XY0
    void op7();

    // 6XNN
    void op8();

    // 7XNN
    void op9();

    // 8XY0
    void op10();

    // 8XY1
    void op11();

    // 8XY2
    void op12();

    // 8XY3
    void op13();
    // 8XY4
    void op14();
    // 8XY5
    // 8XY7
    // 8XY7
    // 8XYE
    // 9XY0
    // ANNN
    // BNNN
    // CXNN
    // DXYN
    void op23();
    // EX9E
    // EXA1
    // FX07
    // FX0A
    // FX15
    // FX18
    // FX1E
    // FX29
    // FX33
    void op32();
    // FX55
    // FX65

public:
    chip8();
    void initialize(const char* name);
    void emulateCycle();
    bool getDrawFlag();
};

#endif // chip8