#ifndef SPELL_DEV_HPP
#define SPELL_DEV_HPP

#include "def/types.hpp"

/////////////////////////////////////////////// 设备ID ///////////////////////////////////////////////
constexpr regsize_t DEV_ID_BAD = -1;    //错误设备
constexpr regsize_t DEV_ID_TERM = 0;   //终端

/////////////////////////////////////////////// 设备端口 ///////////////////////////////////////////////
constexpr regsize_t DEV_TERM_STDIN = 0;      //标准输入
constexpr regsize_t DEV_TERM_STDOUT = 1;  //标准输出
constexpr regsize_t DEV_TERM_STDERR = 2;   //标准错误

#endif