#ifndef SPELL_FLAGS_HPP
#define SPELL_FLAGS_HPP

#include "def/types.hpp"

constexpr regsize_t FLAG_SKIPF = 1;  //控制Machine向前移动到]之后
constexpr regsize_t FLAG_SKIPB = 1 << 1; //控制Machine向后移动到[之后
constexpr regsize_t FLAG_SHUTD = 1 << 2; //终止程序

#endif