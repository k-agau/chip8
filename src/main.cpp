#include "../include/CPU/chip8.h"

chip8 myChip8;

int main(int argc, char **argv) {
    // graphics
    // input
    if(argc || argv == nullptr) {}

    myChip8.initialize("pong");

    while(true) {
        myChip8.emulateCycle();

        if(myChip8.getDrawFlag()) {
            // draw graphics
        }

        // myChip8.setKeys();
    }













    return 0;
}