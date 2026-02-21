#ifndef SPELL_MACHINE_HPP
#define SPELL_MACHINE_HPP

#include <map>
#include "def/types.hpp"
#include "io/Memory.hpp"
#include "io/Reg64Table.hpp"
#include "mach/Instruction.hpp"

class Machine{
public:
    using InstructionMap = std::map<charunit_t, Instruction>;

public:


private:
    
    InstructionMap instructions_;

    void initInstructions();
};

#endif