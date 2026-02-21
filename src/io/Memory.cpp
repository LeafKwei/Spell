#include "io/Memory.hpp"

Memory::Memory() : mem_(MEM_INIT_SIZE, 0){
    
}

void Memory::write(regsize_t addr, memunit_t mu){
    validateAddr(addr);
    mem_[addr] = mu;
}

memunit_t Memory::read(regsize_t addr){
    validateAddr(addr);
    return mem_[addr];
}

void Memory::validateAddr(regsize_t addr){
    if(addr >= mem_.size()) resize(addr);
}

void Memory::resize(regsize_t base){
    std::size_t newsize = static_cast<std::size_t>(base + MEM_RESIZE_INC);
    mem_.resize(newsize);
}

