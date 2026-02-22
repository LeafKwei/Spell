#include "mach/instructions.hpp"
#include "mach/Machine.hpp"
#include "io/impl/MemIO.hpp"
#include "io/impl/RegIO.hpp"
#include "io/RaiiUniIO.hpp"

Machine::Machine(){
    initInstructions();
}

Errno Machine::execute(const std::string &program){
    setup();
    return run(program);
}

void Machine::setup(){
    rtb_ = Reg64Table{};  //借助列表初始化将所有寄存器初始化为0，然后再赋值给rtb_，从而将rtb_中的所有寄存器初始为0
    rtb_.qsx = 1;  //将qsx设置为1，避免plus和subt指令计算倍数相乘时导致结果为0
}

void Machine::initInstructions(){
    /* 基础指令 */
    instructions_.insert({'<', move_mem_left});
    instructions_.insert({'>', move_mem_right});
    instructions_.insert({'[', jump_forward});
    instructions_.insert({']', jump_backward});
    instructions_.insert({'+', plus});
    instructions_.insert({'-', subt});
    instructions_.insert({'!', flip});
    instructions_.insert({'.', setbit});
    instructions_.insert({'~', clrbit});
    instructions_.insert({'(', leftshift});
    instructions_.insert({')', rightshift});
    instructions_.insert({'?', subt_qtx_target});
    instructions_.insert({'*', output_to_terminal});
    instructions_.insert({'&', input_from_terminal});
    instructions_.insert({'#', move_value_to_qtx});
    instructions_.insert({'=', move_value_to_target});
    instructions_.insert({'_', shutdown});

    /* 特殊寄存器选择指令 */
    instructions_.insert({'c', select_qcx});
    instructions_.insert({'o', select_qox});
    instructions_.insert({'p', select_qpx});
    instructions_.insert({'r', select_qrx});
    instructions_.insert({'t', select_qtx});

    /* 内存选择指令 */
    instructions_.insert({'@', select_mem});

    /* 通用寄存器选择指令 */
    instructions_.insert({'0', select_qc0});
    instructions_.insert({'1', select_qc1});
    instructions_.insert({'2', select_qc2});
    instructions_.insert({'3', select_qc3});
    instructions_.insert({'4', select_qc4});
    instructions_.insert({'5', select_qc5});
    instructions_.insert({'6', select_qc6});
    instructions_.insert({'7', select_qc7});
    instructions_.insert({'8', select_qc8});
    instructions_.insert({'9', select_qc9});
}

Errno Machine::run(const std::string &program){
    auto err = OK;

    while(rtb_.qix < program.size() && (!hasFlag(rtb_.qfx, FLAG_SHUTD))){  //指令执行完或遇到停机标志时结束循环
        /* 取出指令，然后递增qix */
        auto ch = program.at(rtb_.qix);
        rtb_.qix++;

        /* 忽略空白等特定字符 */
        if(isIgnored(ch)){
            continue;
        }

        /* 记录跳转标记 */
        

        /* 根据qmx中保存的模式生成对应的寄存器/内存访问对象 */
        RaiiUniIO target(makeUniIO());

        /* 查找指令对应的Instruction */
        auto instptr = instructions_.find(ch);
        if(instptr == instructions_.end()){
            return EBAD_INST;
        }

        /* 执行指令 */
        instptr -> second(&rtb_, target.get());

        /* 检查指令执行错误 */
        err = inspectErr();
        if(err != OK){
            return err;
        }

        /* 检查qfx确认是否需要跳转 */
        err = applyJump(program);
        if(err != OK){
            return err;
        }
    }

    return OK;
}

Errno Machine::inspectErr(){
    auto err = OK;
    err = inspectFlag();
    if(err != OK){
        return err;
    }

    err = inspectMem();
    if(err != OK){
        return err;
    }

    return OK;
}

Errno Machine::inspectFlag(){
    return OK;
}

Errno Machine::inspectMem(){
    if(rtb_.qpx < rtb_.qbx){
        return EOUT_OF_MEM;
    }
    
    return OK;
}

Errno Machine::applyJump(const std::string &program){
    /* 向前跳转 */
    if(hasFlag(rtb_.qfx, FLAG_SKIPF)){
        clrFlag(&rtb_.qfx, FLAG_SKIPF);
        
        auto start = rtb_.qix - 1;  //注意，此时qix已经指向下一条指令(可能是program末尾)，因此需要减1已回到当前指令的位置
        auto end = program.size();
        while(start < end && program.at(start) != ']'){
            ++start;
        }

        /* 到达program末尾仍未找到边界 */
        if(start >= end){
            return ENO_SIDE;
        }

        rtb_.qix = start + 1; //加1是为了跳过]
        return OK;
    }

    /* 向后跳转 */
    if(hasFlag(rtb_.qfx, FLAG_SKIPB)){
        clrFlag(&rtb_.qfx, FLAG_SKIPB);

        auto start = rtb_.qix - 1;
        auto end = -1;
        while(start > end && program.at(start) != '['){
            --start;
        }

        /* 到达program开头仍未找到边界 */
        if(start <= end){
            return ENO_SIDE;
        }

        rtb_.qix = start + 1; //加1是为了跳过[
        return OK;
    }

    return OK;
}

UniIO* Machine::makeUniIO(){
    /* 内存模式 */
    if(rtb_.qmx == MODE_MEM){
        charunit_t *ptr = mem_.ptrof(rtb_.qpx);
        return new MemIO(ptr);
    }

    /* 寄存器模式 */
    regsize_t *ptr = nullptr;
    switch(rtb_.qmx){
        /* 特殊寄存器 */
        case MODE_QAX:
            ptr = &rtb_.qax;
            return new RegIO(ptr);
        case MODE_QBX:
            ptr = &rtb_.qbx;
            return new RegIO(ptr);
        case MODE_QCX:
            ptr = &rtb_.qcx;
            return new RegIO(ptr);
        case MODE_QDX:
            ptr = &rtb_.qdx;
            return new RegIO(ptr);
        case MODE_QEX:
            ptr = &rtb_.qex;
            return new RegIO(ptr);
        case MODE_QFX:
            ptr = &rtb_.qfx;
            return new RegIO(ptr);
        case MODE_QGX:
            ptr = &rtb_.qgx;
            return new RegIO(ptr);
        case MODE_QHX:
            ptr = &rtb_.qhx;
            return new RegIO(ptr);
        case MODE_QIX:
            ptr = &rtb_.qix;
            return new RegIO(ptr);
        case MODE_QJX:
            ptr = &rtb_.qjx;
            return new RegIO(ptr);
        case MODE_QKX:
            ptr = &rtb_.qkx;
            return new RegIO(ptr);
        case MODE_QLX:
            ptr = &rtb_.qlx;
            return new RegIO(ptr);
        case MODE_QMX:
            ptr = &rtb_.qmx;
            return new RegIO(ptr);
        case MODE_QNX:
            ptr = &rtb_.qnx;
            return new RegIO(ptr);
        case MODE_QOX:
            ptr = &rtb_.qox;
            return new RegIO(ptr);
        case MODE_QPX:
            ptr = &rtb_.qpx;
            return new RegIO(ptr);
        case MODE_QQX:
            ptr = &rtb_.qqx;
            return new RegIO(ptr);
        case MODE_QRX:
            ptr = &rtb_.qrx;
            return new RegIO(ptr);
        case MODE_QSX:
            ptr = &rtb_.qsx;
            return new RegIO(ptr);
        case MODE_QTX:
            ptr = &rtb_.qtx;
            return new RegIO(ptr);
        case MODE_QUX:
            ptr = &rtb_.qux;
            return new RegIO(ptr);
        case MODE_QVX:
            ptr = &rtb_.qvx;
            return new RegIO(ptr);
        case MODE_QWX:
            ptr = &rtb_.qwx;
            return new RegIO(ptr);
        case MODE_QXX:
            ptr = &rtb_.qxx;
            return new RegIO(ptr);
        case MODE_QYX:
            ptr = &rtb_.qyx;
            return new RegIO(ptr);
        case MODE_QZX:
            ptr = &rtb_.qzx;
            return new RegIO(ptr);

        /* 通用寄存器 */
        case MODE_QC0:
            ptr = &rtb_.qc0;
            return new RegIO(ptr);   
        case MODE_QC1:
            ptr = &rtb_.qc1;
            return new RegIO(ptr);  
        case MODE_QC2:
            ptr = &rtb_.qc2;
            return new RegIO(ptr);  
        case MODE_QC3:
            ptr = &rtb_.qc3;
            return new RegIO(ptr);  
        case MODE_QC4:
            ptr = &rtb_.qc4;
            return new RegIO(ptr);  
        case MODE_QC5:
            ptr = &rtb_.qc5;
            return new RegIO(ptr);  
        case MODE_QC6:
            ptr = &rtb_.qc6;
            return new RegIO(ptr);  
        case MODE_QC7:
            ptr = &rtb_.qc7;
            return new RegIO(ptr);  
        case MODE_QC8:
            ptr = &rtb_.qc8;
            return new RegIO(ptr);  
        case MODE_QC9:
            ptr = &rtb_.qc9;
            return new RegIO(ptr);  

        default:
            return new RegIO(nullptr);
    }

    return new MemIO(nullptr);
}