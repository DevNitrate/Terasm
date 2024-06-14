#include <iostream>
#include <string>
#include <cmath>

#include "Cpu.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Command use is: 'main <file.emu>'";
        exit(1);
    }

    std::string f = argv[1];
    Cpu cpu(f);

    cpu.execute();

    return 0;
}