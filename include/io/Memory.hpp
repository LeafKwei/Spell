#ifndef SPELL_MEMORY_HPP
#define SPELL_MEMORY_HPP

#include <vector>
#include "def/config.hpp"
#include "def/types.hpp"

/* 对内存的模拟，可以任意访问指定地址的内存单元，当内存地址超出当前内存大小限制时会自动扩容 */
class Memory{
public:
    Memory();
    charunit_t* ptrof(regsize_t addr);
    
private:
    std::vector<memunit_t> mem_;
    void validateAddr(regsize_t addr);
    void resize(regsize_t base);
};

#endif