#ifndef SPELL_INSTRUCTIONS_HPP
#define SPELL_INSTRUCTIONS_HPP

#include <iostream>
#include "def/flags.hpp"
#include "def/modes.hpp"
#include "mach/Instruction.hpp"

/* 此处定义了Machine可以执行的指令 */
inline void move_mem_left(Reg64Table *rtb, UniIO *target){  //内存指针左移
    rtb -> qpx--;
    rtb -> qmx = MODE_MEM;
}

inline void move_mem_right(Reg64Table *rtb, UniIO *target){ //内存指针右移
    rtb -> qpx++;
    rtb -> qmx = MODE_MEM;
}

inline void jump_forward(Reg64Table *rtb, UniIO *target){ //条件检测-前跳
    /* 如果qcx为0，则跳转到右中括号]之后，否则继续执行下一条指令 */
    if(rtb -> qcx == 0){
        rtb -> qfx |= FLAG_SKIPF;
    }
}

inline void jump_backward(Reg64Table *rtb, UniIO *target){ //条件检测-后跳
    /* 如果qcx不为0，则跳转到左中括号之后，否则继续执行下一个指令 */
    if(rtb -> qcx != 0){
        rtb -> qfx |= FLAG_SKIPB;
    }
}

inline void plus(Reg64Table *rtb, UniIO *target){ //递增1
    target -> out(target -> in() + 1);
}

inline void subt(Reg64Table *rtb, UniIO *target){ //递减1
    target -> out(target -> in() - 1);
}

inline void leftshift(Reg64Table *rtb, UniIO *target){ //左移1位
    target -> out((target -> in() << 1));
}

inline void output_to_terminal(Reg64Table *rtb, UniIO *target){ //输出
    charunit_t ch = static_cast<charunit_t>(target -> in());
    std::cout << ch;
}

inline void input_from_terminal(Reg64Table *rtb, UniIO *target) { //输入
    charunit_t ch;
    std::cin >> ch;
    target -> out(ch);
}

inline void clear(Reg64Table *rtb, UniIO *target){ //清零
    target -> out(0);
}

inline void move_value_to_qtx(Reg64Table *rtb, UniIO *target){ //将操作对象保存到qtx
    rtb -> qtx = target -> in();
}

inline void move_value_to_target(Reg64Table *rtb, UniIO *target){ //将qtx保存到操作对象
    target -> out(rtb -> qtx);
}

inline void subt_qtx_target(Reg64Table *rtb, UniIO *target){ //将qtx与操作对象相减，结果保存到qrx
    rtb -> qrx = (rtb -> qtx) - (target -> in()); 
}

inline void shutdown(Reg64Table *rtb, UniIO *target){ //停机
    rtb -> qfx |= FLAG_SHUTD;
}

/* 内存使能函数 */
inline void select_mem(Reg64Table *rtb, UniIO *target){ //选择内存访问
    rtb -> qmx = MODE_MEM;
}

/* 特殊寄存器的使能函数，对于用户不可访问的特殊寄存器则不定义相关函数 */
inline void select_qcx(Reg64Table *rtb, UniIO *target){ //选择qcx为操作对象
    rtb -> qmx = MODE_QCX;
}

inline void select_qpx(Reg64Table *rtb, UniIO *target){ //选择qpx为操作对象
    rtb -> qmx = MODE_QPX;
}

inline void select_qrx(Reg64Table *rtb, UniIO *target){  //选择qrx为操作对象
    rtb -> qmx = MODE_QRX;
}

inline void select_qtx(Reg64Table *rtb, UniIO *target){ //选择qtx为操作对象
    rtb -> qmx = MODE_QTX;
}

/* 通用寄存器的使能函数 */
inline void select_qc0(Reg64Table *rtb, UniIO *target){ //选择qc0为操作对象
    rtb -> qmx = MODE_QC0;
}

inline void select_qc1(Reg64Table *rtb, UniIO *target){ //选择qc1为操作对象
    rtb -> qmx = MODE_QC1;
}

inline void select_qc2(Reg64Table *rtb, UniIO *target){ //选择qc2为操作对象
    rtb -> qmx = MODE_QC2;
}

inline void select_qc3(Reg64Table *rtb, UniIO *target){ //选择qc3为操作对象
    rtb -> qmx = MODE_QC3;
}

inline void select_qc4(Reg64Table *rtb, UniIO *target){ //选择qc4为操作对象
    rtb -> qmx = MODE_QC4;
}

inline void select_qc5(Reg64Table *rtb, UniIO *target){ //选择qc5为操作对象
    rtb -> qmx = MODE_QC5;
}

inline void select_qc6(Reg64Table *rtb, UniIO *target){ //选择qc6为操作对象
    rtb -> qmx = MODE_QC6;
}

inline void select_qc7(Reg64Table *rtb, UniIO *target){ //选择qc7为操作对象
    rtb -> qmx = MODE_QC7;
}

inline void select_qc8(Reg64Table *rtb, UniIO *target){ //选择qc8为操作对象
    rtb -> qmx = MODE_QC8;
}

inline void select_qc9(Reg64Table *rtb, UniIO *target){ //选择qc9为操作对象
    rtb -> qmx = MODE_QC9;
}

#endif