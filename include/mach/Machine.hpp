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
    InstructionMap   instructions_;
    const std::string *program_;

    void setup();
    void initInstructions();
    Errno   run(const std::string &program);
    UniIO* makeUniIO();

    /* 错误处理及特殊功能函数 */
    void dealwithMem();
    void dealwithFlag();
    void do_dealwithFlag_Jmp();

    /* 工具函数 */
    bool isIgnored(char ch) const noexcept;
    bool hasFlag(regsize_t flag) const noexcept;
    void setFlag(regsize_t flag) noexcept;
    void clrFlag(regsize_t flag) noexcept;
};

inline bool Machine::isIgnored(char ch) const noexcept{
    if(std::isblank(ch)){
        return true;
    }

    return false;
}

inline bool Machine::hasFlag(regsize_t flag) const noexcept{
    return rtb_.qfx & flag;
}

inline void Machine::setFlag(regsize_t flag) noexcept{
    rtb_.qfx |= flag;
}

inline void Machine::clrFlag(regsize_t flag) noexcept{
    rtb_.qfx &= (~flag);
}

#endif