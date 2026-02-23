#ifndef SPELL_CONFIG_HPP
#define SPELL_CONFIG_HPP

constexpr int MEM_INIT_SIZE = 0xFFFF;    //初始内存大小
constexpr int MEM_RESIZE_INC = 0xFFFF; //内存扩容时在addr的基础上的增量
constexpr int PORT_BLOCK_SIZE = 32;      //以此数量为单位为每个设备分配端口

#endif