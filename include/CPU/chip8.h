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
    // Functions
    // 0NNN
    void op0(unsigned short op);

    // 00E0
    void op1(unsigned short op);

    // 00EE
    void op2(unsigned short op);

    // 1NNN
    void op3(unsigned short op);

    // 2NNN


    // 3XNN


    // 4XNN


    // 5XY0


    // 6XNN

public:
    chip8();
    void initialize(const char* name);
    void emulateCycle();
    bool getDrawFlag();
};

#endif // chip8