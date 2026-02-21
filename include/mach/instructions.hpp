#ifndef SPELL_INSTRUCTIONS_HPP
#define SPELL_INSTRUCTIONS_HPP

#include <iostream>
#include "def/flags.hpp"
#include "mach/Instruction.hpp"

/* 此处定义了Machine可以执行的指令 */
inline void move_mem_left(Reg64Table *rtb, Memory *mem, UniIO *target){  //<
    rtb -> qpx--;
}

inline void move_mem_right(Reg64Table *rtb, Memory *mem, UniIO *target){ //>
    rtb -> qpx++;
}

inline void jump_forward(Reg64Table *rtb, Memory *mem, UniIO *target){ //[
    if(rtb -> qcx != 0) return;
    rtb -> qfx |= FLAG_SKIPF;
}

inline void jump_backward(Reg64Table *rtb, Memory *mem, UniIO *target){ //]
    if(rtb -> qcx == 0) return;
    rtb -> qfx |= FLAG_SKIPB;
}

inline void plus(Reg64Table *rtb, Memory *mem, UniIO *target){ //+
    regsize_t data = target -> in();
    auto scale = (rtb -> qsx != 0) ? rtb -> qsx : 1;
    auto adjust = rtb -> qax;
    data = (data + (scale * (adjust + 1)));
    target -> out(data);
}

inline void subt(Reg64Table *rtb, Memory *mem, UniIO *target){ //-
    regsize_t data = target -> in();
    auto scale = (rtb -> qsx != 0) ? rtb -> qsx : 1;
    auto adjust = rtb -> qax;
    data = (data - (scale * (adjust + 1)));
    target -> out(data);
}

inline void output_from_terminal(Reg64Table *rtb, Memory *mem, UniIO *target){ //$
    charunit_t ch = static_cast<charunit_t>(target -> in());
    std::cout << ch;
}

inline void input_from_terminal(Reg64Table *rtb, Memory *mem, UniIO *target) { //&
    charunit_t ch;
    std::cin >> ch;
    target -> out(ch);
}

inline void clear(Reg64Table *rtb, Memory *mem, UniIO *target){ //~
    target -> out(0);
}

inline void move_value_to_qtx(Reg64Table *rtb, Memory *mem, UniIO *target){ //=
    rtb -> qtx = target -> in();
}

inline void move_value_to_target(Reg64Table *rtb, Memory *mem, UniIO *target){ //#
    target -> out(rtb -> qtx);
}

inline void subt_qtx_target(Reg64Table *rtb, Memory *mem, UniIO *target){ //?
    rtb -> qrx = (rtb -> qtx) - (target -> in()); 
}

inline void shutdown(Reg64Table *rtb, Memory *mem, UniIO *target){ //!
    rtb -> qfx |= FLAG_SHUTD;
}

#endif