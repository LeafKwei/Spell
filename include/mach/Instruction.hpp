#ifndef SPELL_INSTRUCTION_HPP
#define SPELL_INSTRUCTION_HPP

#include <functional>
#include "io/mem/Memory.hpp"
#include "io/reg/Reg64Table.hpp"
#include "io/UniIO.hpp"

/* 指令定义 */
using Instruction = std::function<void(Reg64Table *rtb, UniIO *target)>;

#endif