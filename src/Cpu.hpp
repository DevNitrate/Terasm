#pragma once
#include <vector>
#include <string>

// [reg_1] [reg_2] [reg_3] [reg_4] [addr] [res] [if]
// set <reg> <val> - sets the register to the value
// setr <reg1> <reg2> - sets the reg1 to the value of reg2
// add - add register 1 and 2
// sub - substracts register 1 and 2
// mul - multiplies register 1 and 2
// div - divides register 1 and 2
// clear - clears the result register
// print - prints value in result register
// printa - prints value in result register as ascii
// save <val> - saves val in ram and set address register to the storing adress
// saver <reg> - saves the value in reg into ram
// load <reg> - puts the value of the ram at address addr into reg
// start - restarts the program from first instruction
// inc <reg> - increments the register by 1
// startif - jumps to start if the if register is true
// jmpif <line> - jumps to the line of asm if register is true
// jmp - jumps to the line of asm
// smaller <reg1> <reg2> - set if register to true if reg1 is smaller than reg2
// greater <reg1> <reg2> - set if register to true if reg1 is greater than reg2
// equal <reg1> <reg2> - set if register to true if reg1 is equal to reg2
// skipins - skips instruction if the if register is true
// nothing - does nothing

enum class InstructionType {
    set,
    setr,
    add,
    sub,
    mul,
    div,
    clear,
    print,
    printa,
    save,
    saver,
    load,
    start,
    inc,
    jmpif,
    startif,
    jmp,
    smaller,
    greater,
    equal,
    skipins,
    nothing
};

struct Instruction {
    InstructionType op;
    std::string arg1;
    std::string arg2;
};

class Cpu {
public:
    Cpu(const std::string& f);

    int reg_1;
    int reg_2;
    int reg_3;
    int reg_4;
    int addr;
    int res;
    bool if_reg;
    int lastRam;

    std::vector<Instruction> instructions;
    int ram[65535];

    void execute();
};