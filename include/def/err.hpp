#ifndef SPELL_ERR_HPP
#define SPELL_ERR_HPP

#include <stdexcept>

using Errno = unsigned int;

constexpr Errno OK = 0;
constexpr Errno EOUT_OF_MEM = 1;  //内存指针移动到了qbx允许的界限外
constexpr Errno EBAD_INST = 5;         //非预期的指令
constexpr Errno EBAD_IO = 6;             //IO错误
constexpr Errno ENO_SIDE = 10;         //跳转/循环指令没有另一侧的边界

class SpellExcept : public std::logic_error{
public:
    SpellExcept(Errno err) : logic_error(""), errno_(err){}
    SpellExcept(const std::string &msg, Errno err) : logic_error(msg), errno_(err){}
    Errno err(){ return errno_;}
private:
    Errno errno_;
};

#endif