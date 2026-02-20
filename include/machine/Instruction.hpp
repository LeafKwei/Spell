#ifndef SPELL_INSTRUCTION_HPP
#define SPELL_INSTRUCTION_HPP

#include <functional>
#include "Memory.hpp"
#include "Reg64Struct.hpp"

using Instruction = std::function<void(Reg64Struct &reg, Memory &mem)>;

#endif