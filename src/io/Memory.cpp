#include "io/Memory.hpp"

Memory::Memory() : mem_(MEM_INIT_SIZE, 0){
    
}

charunit_t* Memory::ptrof(regsize_t addr){
    validateAddr(addr);
    return &(mem_.at(addr));
}

void Memory::validateAddr(regsize_t addr){
    if(addr >= mem_.size()) resize(addr);
}

void Memory::resize(regsize_t base){
    std::size_t newsize = static_cast<std::size_t>(base + MEM_RESIZE_INC);
    mem_.resize(newsize);
}

