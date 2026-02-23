#ifndef SPELL_REG64Table_HPP
#define SPELL_REG64Table_HPP

#include "def/types.hpp"

/* 声明所有寄存器，未注释的寄存器均为保留寄存器，并未实际应用(字母q表示quad word) */
struct Reg64Table{
    /* 专用寄存器，拥有特殊的作用，用户通过修改这些寄存器可实现某些特殊功能，不推荐将这些寄存器当作通用寄存器使用 */
    regsize_t qax;
    regsize_t qbx;    //基址寄存器(base)，保存用户可访问的内存的起始地址
    regsize_t qcx;    //计数/条件寄存器(count/condition)
    regsize_t qdx;    //设备寄存器(device)，用作以后对模拟设备的访问
    regsize_t qex;
    regsize_t qfx;    //标志寄存器(flag)，记录控制Machine运行的标志
    regsize_t qgx;
    regsize_t qhx;
    regsize_t qix;     //指令寄存器(instruction)，记录下一个执行的指令的位置
    regsize_t qjx;
    regsize_t qkx;
    regsize_t qlx;
    regsize_t qmx;  //模式寄存器(mode)，记录Machine的数据访问模式
    regsize_t qnx;
    regsize_t qox;   //偏移量寄存器(offset)，记录某些操作所需的偏移量
    regsize_t qpx;   //指针寄存器(pointer)，指向当前所在的内存地址
    regsize_t qqx;
    regsize_t qrx;   //结果寄存器(result)，记录某些操作的结果
    regsize_t qsx;
    regsize_t qtx;  //临时寄存器(temp)，用于寄存器、内存间的数据交换
    regsize_t qux;
    regsize_t qvx;
    regsize_t qwx;
    regsize_t qxx;
    regsize_t qyx;
    regsize_t qzx;

    /* 通用寄存器，用户可自由使用这些寄存器(字母c表示common)*/
    regsize_t qc0;
    regsize_t qc1;
    regsize_t qc2;
    regsize_t qc3;
    regsize_t qc4;
    regsize_t qc5;
    regsize_t qc6;
    regsize_t qc7;
    regsize_t qc8;
    regsize_t qc9;
};


#endif