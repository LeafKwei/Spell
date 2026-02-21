#ifndef SPELL_UNIIO_HPP
#define SPELL_UNIIO_HPP

#include "def/types.hpp"

constexpr int UNIIO_ID_MEM= 0;  //内存
constexpr int UNIIO_ID_REG = 1;   //寄存器

/* 统一寄存器与内存访问方式 */
class UniIO{
public:
    virtual ~UniIO() =default;
    virtual int           id() =0;    //不同访问方式的标识
    virtual regsize_t in() =0;    //读取数据
    virtual void        out(regsize_t data) =0; //写入数据
};

#endif