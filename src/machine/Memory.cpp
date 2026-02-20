#include "Memory.hpp"

Memory::Memory(double capfactor) 
    : capfactor_(capfactor)
    , mem_(MEM_INIT_SIZE, 0)
{
    
}

void Memory::write(regsize_t addr, memunit_t mu){
    if(addr >= mem_.size()) resize();
    mem_[addr] = mu;
}

memunit_t Memory::read(regsize_t addr){
    if(addr >= mem_.size()) resize();
    return mem_[addr];
}

void Memory::resize(){
    std::size_t newsize = static_cast<std::size_t>(mem_.size() * capfactor_);
    mem_.resize(newsize);
}

