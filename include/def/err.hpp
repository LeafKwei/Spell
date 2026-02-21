#ifndef SPELL_ERR_HPP
#define SPELL_ERR_HPP

using Errno = unsigned int;

constexpr Errno OK = 0;
constexpr Errno EOUT_OF_MEM = 1;  //内存指针移动到了qbx允许的界限外
constexpr Errno EBAD_INST = 2;         //非预期的指令
constexpr Errno ENO_SIDE = 3;           //跳转/循环指令没有另一侧的边界

#endif