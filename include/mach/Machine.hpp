#ifndef SPELL_MACHINE_HPP
#define SPELL_MACHINE_HPP

#include <map>
#include <string>
#include "def/err.hpp"
#include "def/types.hpp"
#include "io/Memory.hpp"
#include "io/Reg64Table.hpp"
#include "mach/Instruction.hpp"

class Machine{
public:
    using InstructionMap = std::unordered_map<charunit_t, Instruction>;

public:
    Machine();
    Errno execute(const std::string &program);

private:
    Reg64Table rtb_;
    Memory      mem_;
    InstructionMap instructions_;

    void setup();
    void initInstructions();
    Errno   run(const std::string &program);
    UniIO* makeUniIO();
    Errno inspectErr();
    Errno inspectFlag();
    Errno inspectMem();
    Errno applyJump(const std::string &program);
    bool hasFlag(regsize_t reg, regsize_t flag) const noexcept;
    void setFlag(regsize_t *reg, regsize_t flag) noexcept;
    void clrFlag(regsize_t *reg, regsize_t flag) noexcept;
};

inline bool Machine::hasFlag(regsize_t reg, regsize_t flag) const noexcept{
    return reg & flag;
}

inline void Machine::setFlag(regsize_t *reg, regsize_t flag) noexcept{
    (*reg) = (*reg) | flag;
}

inline void Machine::clrFlag(regsize_t *reg, regsize_t flag) noexcept{
    (*reg) = (*reg) & (~flag);
}

#endif