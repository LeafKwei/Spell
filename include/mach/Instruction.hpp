#ifndef SPELL_INSTRUCTION_HPP
#define SPELL_INSTRUCTION_HPP

#include <functional>
#include "io/Memory.hpp"
#include "io/Reg64Table.hpp"
#include "io/UniIO.hpp"

/* 指令定义 */
using Instruction = std::function<void(Reg64Table *rtb, Memory *mem, UniIO *target)>;

#endif