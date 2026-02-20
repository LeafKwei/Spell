#ifndef SPELL_MACHINE_HPP
#define SPELL_MACHINE_HPP

#include <map>
#include "types.hpp"
#include "Instruction.hpp"
#include "Memory.hpp"
#include "Reg64Struct.hpp"

class Machine{
public:
    using InstructionMap = std::map<charunit_t, Instruction>;

public:


private:
    
    InstructionMap instructions_;

    void initInstructions();
};

#endif