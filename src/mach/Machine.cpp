#include "mach/instructions.hpp"
#include "mach/Machine.hpp"

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
    instructions_.insert({',', output_to_terminal});
    instructions_.insert({'.', input_from_terminal});
    instructions_.insert({';', output_to_device});
    instructions_.insert({':', input_from_device});
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
    program_ = &program;

    while(rtb_.qix < program.size() && (!hasFlag(FLAG_SHUTD))){  //指令执行完或遇到停机标志时结束循环
        /* 取出指令，然后递增qix */
        auto ch = program.at(rtb_.qix);
        rtb_.qix++;

        /* 忽略空白等特定字符 */
        if(isIgnored(ch)){
            continue;
        }

        /* 根据qmx中保存的模式生成对应的寄存器/内存访问对象 */
        UniIO *uiop = makeUniIO();

        /* 查找指令对应的Instruction */
        auto instptr = instructions_.find(ch);
        if(instptr == instructions_.end()){
            return EBAD_INST;
        }

        /* 执行指令 */
        instptr -> second(&rtb_, uiop);

        /* 检查内存、标志等信息 */
        try{
            dealwithMem();
            dealwithFlag();
        }catch(SpellExcept se){
            return se.err();
        }
    }

    return OK;
}

void Machine::dealwithMem(){
    /* 内存指针小于qbx规定的最小界限时抛出异常 */
    if(rtb_.qpx < rtb_.qbx){
        throw SpellExcept(EOUT_OF_MEM);
    }
}

void Machine::dealwithFlag(){
    /* 处理跳转标志 */
    if(hasFlag(FLAG_JMPF | FLAG_JMPB)) do_dealwithFlag_Jmp();
}

void Machine::do_dealwithFlag_Jmp(){
    decltype(rtb_.qix) newqix = 0;

    /* 前向跳转 */
    if(hasFlag(FLAG_JMPF)){
        clrFlag(FLAG_JMPF);

        auto start = rtb_.qix - 1;  //减1是为了回到指令 [ 的位置，避免因为qix自增后超出program字符串的长度
        auto end = program_-> size();
        auto cnt = -1;

        while(start < end){
            auto ch = program_-> at(start++);

            /* 遇到右括号时，检查左括号计数是否为0，不为0则继续查找，否则结束查找 */
            if(ch == ']'){
                if(cnt > 0){
                    --cnt;
                    continue;
                }

                newqix = start;
                break;
            }

            /* 遇到左括号时递增计数，避免因括号嵌套从而导致错误的跳转 */
            if(ch == '['){
                ++cnt;
            }
        }

        if(start >= end){
            throw SpellExcept(ENO_SIDE);
        }
    }
    /* 后向跳转 */
    else{
        clrFlag(FLAG_JMPB);

        auto start = rtb_.qix - 1;  //减1是为了回到指令 [ 的位置，避免因为qix自增后超出program字符串的长度
        auto end = -1;
        auto cnt = -1;  //避免将当前位置的括号计入到cnt中

        while(start > end){
            auto ch = program_-> at(start--);

            /* 遇到左括号时，检查右括号计数是否为0，不为0则继续查找，否则结束查找 */
            if(ch == '['){
                if(cnt > 0){
                    --cnt;
                    continue;
                }

                newqix = start;
                break;
            }

            /* 遇到右括号时递增计数，避免因括号嵌套从而导致错误的跳转 */
            if(ch == ']'){
                ++cnt;
            }
        }

        if(start <= end){
            throw SpellExcept(ENO_SIDE);
        }
    }

    /* 修改qix以实现跳转 */
    rtb_.qix = newqix;
}

UniIO* Machine::makeUniIO(){
    switch(rtb_.qmx){
        case MODE_MEM:
            return make_mem_io();
        case MODE_DEV:
            return make_dev_io();
        default:
            return make_reg_io();
    }
}

UniIO* Machine::make_mem_io(){
    charunit_t *ptr = mem_.ptrof(rtb_.qpx);
    memio_.setptr(ptr);
    return &memio_;
}

UniIO* Machine::make_dev_io(){
    
}

UniIO* Machine::make_reg_io(){
    regsize_t *ptr = nullptr;
    switch(rtb_.qmx){
        /* 特殊寄存器 */
        case MODE_QAX:
            ptr = &rtb_.qax;
            break;
        case MODE_QBX:
            ptr = &rtb_.qbx;
            break;
        case MODE_QCX:
            ptr = &rtb_.qcx;
            break;
        case MODE_QDX:
            ptr = &rtb_.qdx;
            break;
        case MODE_QEX:
            ptr = &rtb_.qex;
            break;
        case MODE_QFX:
            ptr = &rtb_.qfx;
            break;
        case MODE_QGX:
            ptr = &rtb_.qgx;
            break;
        case MODE_QHX:
            ptr = &rtb_.qhx;
            break;
        case MODE_QIX:
            ptr = &rtb_.qix;
            break;
        case MODE_QJX:
            ptr = &rtb_.qjx;
            break;
        case MODE_QKX:
            ptr = &rtb_.qkx;
            break;
        case MODE_QLX:
            ptr = &rtb_.qlx;
            break;
        case MODE_QMX:
            ptr = &rtb_.qmx;
            break;
        case MODE_QNX:
            ptr = &rtb_.qnx;
            break;
        case MODE_QOX:
            ptr = &rtb_.qox;
            break;
        case MODE_QPX:
            ptr = &rtb_.qpx;
            break;
        case MODE_QQX:
            ptr = &rtb_.qqx;
            break;
        case MODE_QRX:
            ptr = &rtb_.qrx;
            break;
        case MODE_QSX:
            ptr = &rtb_.qsx;
            break;
        case MODE_QTX:
            ptr = &rtb_.qtx;
            break;
        case MODE_QUX:
            ptr = &rtb_.qux;
            break;
        case MODE_QVX:
            ptr = &rtb_.qvx;
            break;
        case MODE_QWX:
            ptr = &rtb_.qwx;
            break;
        case MODE_QXX:
            ptr = &rtb_.qxx;
            break;
        case MODE_QYX:
            ptr = &rtb_.qyx;
            break;
        case MODE_QZX:
            ptr = &rtb_.qzx;
            break;

        /* 通用寄存器 */
        case MODE_QC0:
            ptr = &rtb_.qc0;
            break;   
        case MODE_QC1:
            ptr = &rtb_.qc1;
            break;  
        case MODE_QC2:
            ptr = &rtb_.qc2;
            break;  
        case MODE_QC3:
            ptr = &rtb_.qc3;
            break;  
        case MODE_QC4:
            ptr = &rtb_.qc4;
            break;  
        case MODE_QC5:
            ptr = &rtb_.qc5;
            break;  
        case MODE_QC6:
            ptr = &rtb_.qc6;
            break;  
        case MODE_QC7:
            ptr = &rtb_.qc7;
            break;  
        case MODE_QC8:
            ptr = &rtb_.qc8;
            break;  
        case MODE_QC9:
            ptr = &rtb_.qc9;
            break;  
        default:
            ptr = nullptr;
    }

    regio_.setptr(ptr);
    return &regio_;
}