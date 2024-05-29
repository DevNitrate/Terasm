#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Cpu.hpp"

Cpu::Cpu(const std::string& f) {
    std::vector<Instruction> instructions;
    std::string line;

    std::ifstream file(f);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string l = iss.str();

        std::string strBuf;
        std::string argBuf1 = "";
        std::string argBuf2 = "";
        bool isArg = false;
        int argCount = 0;

        for (int i = 0; i < l.length(); i++) {
            char c = l.at(i);

            if (isalnum(c)) {
                if (isArg) {
                    if (argCount == 1) {
                        argBuf1.push_back(c);
                    } else if (argCount == 2) {
                        argBuf2.push_back(c);
                    } else {
                        std::cerr << "Wrong number of args";
                        exit(1);
                    }
                } else {
                    strBuf.push_back(c);
                }
            } else if (c == ' ') {
                isArg = true;
                argCount++;
            }

            if (i == l.length() - 1) {
                if (strBuf == "set") {
                    Instruction instruction = Instruction {
                        InstructionType::set,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "setr") {
                    Instruction instruction = Instruction {
                        InstructionType::setr,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "add") {
                    Instruction instruction = Instruction {
                        InstructionType::add,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "sub") {
                    Instruction instruction = Instruction {
                        InstructionType::sub,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "mul") {
                    Instruction instruction = Instruction {
                        InstructionType::mul,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "div") {
                    Instruction instruction = Instruction {
                        InstructionType::div,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "clear") {
                    Instruction instruction = Instruction {
                        InstructionType::clear,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "print") {
                    Instruction instruction = Instruction {
                        InstructionType::print,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "printa") {
                    Instruction instruction = Instruction {
                        InstructionType::printa,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "save") {
                    Instruction instruction = Instruction {
                        InstructionType::save,
                        argBuf1
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "saver") {
                    Instruction instruction = Instruction {
                        InstructionType::saver,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "load") {
                    Instruction instruction = Instruction {
                        InstructionType::load,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "start") {
                    Instruction instruction = Instruction {
                        InstructionType::start,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "inc") {
                    Instruction instruction = Instruction {
                        InstructionType::inc,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "jmpif") {
                    Instruction instruction = Instruction {
                        InstructionType::jmpif,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "startif") {
                    Instruction instruction = Instruction {
                        InstructionType::startif,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "jmp") {
                    Instruction instruction = Instruction {
                        InstructionType::jmp,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "smaller") {
                    Instruction instruction = Instruction {
                        InstructionType::smaller,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "greater") {
                    Instruction instruction = Instruction {
                        InstructionType::greater,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "equal") {
                    Instruction instruction = Instruction {
                        InstructionType::equal,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "skipins") {
                    Instruction instruction = Instruction {
                        InstructionType::skipins,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else if (strBuf == "nothing") {
                    Instruction instruction = Instruction {
                        InstructionType::nothing,
                        argBuf1,
                        argBuf2
                    };

                    instructions.push_back(instruction);
                } else {
                    std::cerr << "unknown token: " << strBuf;
                    exit(1);
                }
            }
        }

    }

    file.close();

    this->reg_1 = 0;
    this->reg_2 = 0;
    this->addr = 0;
    this->res = 0;
    this->lastRam = 0;
    this->if_reg = false;
    this->instructions = instructions;
}

void Cpu::execute() {
    for (int i = 0; i < this->instructions.size(); i++) {
        Instruction instruction = this->instructions[i];

        if (instruction.op == InstructionType::set) {
            int arg2 = std::stoi(instruction.arg2);
            if (instruction.arg1 == "r1") {
                this->reg_1 = arg2;
            } else if (instruction.arg1 == "r2") {
                this->reg_2 = arg2;
            } else if (instruction.arg1 == "addr") {
                this->addr = arg2;
            } else if (instruction.arg1 == "if") {
                if (arg2 == 0) {
                    this->if_reg = false;
                } else if (arg2 == 1) {
                    this->if_reg = true;
                } else {
                    std::cerr << "on line " << i+1 << ": ";
                    std::cerr << "You can only set if register to 0 or 1";
                    exit(1);
                }
            } else if (instruction.arg1 == "res") {
                this->res = arg2;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg1;
                exit(1);
            }
        }if (instruction.op == InstructionType::setr) {
            int arg2;

            if (instruction.arg2 == "r1") {
                arg2 = this->reg_1;
            } else if (instruction.arg2 == "r2") {
                arg2 = this->reg_2;
            } else if (instruction.arg2 == "addr") {
                arg2 = this->addr;
            } else if (instruction.arg2 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot use setr with if register ";
                exit(1);
            } else if (instruction.arg2 == "res") {
                arg2 = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg2;
                exit(1);
            }

            if (instruction.arg1 == "r1") {
                this->reg_1 = arg2;
            } else if (instruction.arg1 == "r2") {
                this->reg_2 = arg2;
            } else if (instruction.arg1 == "addr") {
                this->addr = arg2;
            } else if (instruction.arg1 == "if") {
                if (arg2 == 0) {
                    this->if_reg = false;
                } else if (arg2 == 1) {
                    this->if_reg = true;
                } else {
                    std::cerr << "on line " << i+1 << ": ";
                    std::cerr << "You can only set if register to 0 or 1";
                    exit(1);
                }
            } else if (instruction.arg1 == "res") {
                this->res = arg2;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg1;
                exit(1);
            }
        } else if (instruction.op == InstructionType::add) {
            this->res = this->reg_1 + this->reg_2;
        } else if (instruction.op == InstructionType::sub) {
            this->res = this->reg_1 - this->reg_2;
        } else if (instruction.op == InstructionType::mul) {
            this->res = this->reg_1 * this->reg_2;
        } else if (instruction.op == InstructionType::div) {
            this->res = this->reg_1 / this->reg_2;
        } else if (instruction.op == InstructionType::clear) {
            this->res = 0;
        } else if (instruction.op == InstructionType::print) {
            std::cout << res << "\n";
        } else if (instruction.op == InstructionType::printa) {
            std::cout << (char)res << "\n";
        } else if (instruction.op == InstructionType::save) {
            int arg = std::stoi(instruction.arg1);
            this->ram[lastRam] = arg;
            this->addr = lastRam;
            this->lastRam++;
        } else if (instruction.op == InstructionType::saver) {
            std::string arg = instruction.arg1;

            if (arg == "r1") {
                this->ram[lastRam] = this->reg_1;
            } else if (arg == "r2") {
                this->ram[lastRam] = this->reg_2;
            } else if (arg == "addr") {
                this->ram[lastRam] = this->addr;
            } else if (arg == "if") {
                this->ram[lastRam] = this->if_reg;
            } else if (arg == "res") {
                this->ram[lastRam] = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << arg;
                exit(1);
            }

            this->addr = lastRam;
            this->lastRam++;
        } else if (instruction.op == InstructionType::load) {
            std::string arg = instruction.arg1;

            if (arg == "r1") {
                this->reg_1 = this->ram[this->addr];
            } else if (arg == "r2") {
                this->reg_2 = this->ram[this->addr];
            } else if (arg == "addr") {
                this->addr = this->ram[this->addr];
            } else if (arg == "if") {
                this->if_reg = this->ram[this->addr];
            } else if (arg == "res") {
                this->res = this->ram[this->addr];
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << arg;
                exit(1);
            }

            this->lastRam--;
            this->addr = lastRam;
        } else if (instruction.op == InstructionType::start) {
            i = -1;
        } else if (instruction.op == InstructionType::jmp) {
            int arg = std::stoi(instruction.arg1);
            i = arg - 2;
        } else if (instruction.op == InstructionType::inc) {
            if (instruction.arg1 == "r1") {
                this->reg_1++;
            } else if (instruction.arg1 == "r2") {
                this->reg_2++;
            } else if (instruction.arg1 == "addr") {
                this->addr++;
            } else if (instruction.arg1 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot inc the if register ";
                exit(1);
            } else if (instruction.arg1 == "res") {
                this->res++;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg1;
                exit(1);
            }
        } else if (instruction.op == InstructionType::startif) {
            if (this->if_reg) {
                i = -1;
            }
        } else if (instruction.op == InstructionType::jmpif) {
            if (this->if_reg) {
                int arg = std::stoi(instruction.arg1);
                i = arg - 2;
            }
        } else if (instruction.op == InstructionType::smaller) {
            int reg1 = 0;
            int reg2 = 0;

            if (instruction.arg1 == "r1") {
                reg1 = this->reg_1;
            } else if (instruction.arg1 == "r2") {
                reg1 = this->reg_2;
            } else if (instruction.arg1 == "addr") {
                reg1 = this->addr;
            } else if (instruction.arg1 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot use smaller with if register ";
                exit(1);
            } else if (instruction.arg1 == "res") {
                reg1 = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg1;
                exit(1);
            }

            if (instruction.arg2 == "r1") {
                reg2 = this->reg_1;
            } else if (instruction.arg2 == "r2") {
                reg2 = this->reg_2;
            } else if (instruction.arg2 == "addr") {
                reg2 = this->addr;
            } else if (instruction.arg2 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot use smaller with if register ";
                exit(1);
            } else if (instruction.arg2 == "res") {
                reg2 = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg2;
                exit(1);
            }

            if (reg1 < reg2) {
                this->if_reg = true;
            } else {
                this->if_reg = false;
            }
        } else if (instruction.op == InstructionType::greater) {
            int reg1 = 0;
            int reg2 = 0;

            if (instruction.arg1 == "r1") {
                reg1 = this->reg_1;
            } else if (instruction.arg1 == "r2") {
                reg1 = this->reg_2;
            } else if (instruction.arg1 == "addr") {
                reg1 = this->addr;
            } else if (instruction.arg1 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot use greater with if register ";
                exit(1);
            } else if (instruction.arg1 == "res") {
                reg1 = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg1;
                exit(1);
            }

            if (instruction.arg2 == "r1") {
                reg2 = this->reg_1;
            } else if (instruction.arg2 == "r2") {
                reg2 = this->reg_2;
            } else if (instruction.arg2 == "addr") {
                reg2 = this->addr;
            } else if (instruction.arg2 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot use greater with if register ";
                exit(1);
            } else if (instruction.arg2 == "res") {
                reg2 = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg2;
                exit(1);
            }

            if (reg1 > reg2) {
                this->if_reg = true;
            } else {
                this->if_reg = false;
            }
        } else if (instruction.op == InstructionType::equal) {
            int reg1 = 0;
            int reg2 = 0;

            if (instruction.arg1 == "r1") {
                reg1 = this->reg_1;
            } else if (instruction.arg1 == "r2") {
                reg1 = this->reg_2;
            } else if (instruction.arg1 == "addr") {
                reg1 = this->addr;
            } else if (instruction.arg1 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot use equal with if register ";
                exit(1);
            } else if (instruction.arg1 == "res") {
                reg1 = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg1;
                exit(1);
            }

            if (instruction.arg2 == "r1") {
                reg2 = this->reg_1;
            } else if (instruction.arg2 == "r2") {
                reg2 = this->reg_2;
            } else if (instruction.arg2 == "addr") {
                reg2 = this->addr;
            } else if (instruction.arg2 == "if") {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "You cannot use equal with if register ";
                exit(1);
            } else if (instruction.arg2 == "res") {
                reg2 = this->res;
            } else {
                std::cerr << "on line " << i+1 << ": ";
                std::cerr << "Unknown register: " << instruction.arg2;
                exit(1);
            }

            if (reg1 == reg2) {
                this->if_reg = true;
            } else {
                this->if_reg = false;
            }
        } else if (instruction.op == InstructionType::skipins) {
            if (this->if_reg) {
                i++;
            }
        } else if (instruction.op == InstructionType::nothing) {
            continue;
        }
    }
}