#ifndef SPELL_MEMORY_HPP
#define SPELL_MEMORY_HPP

#include <vector>
#include "config.hpp"
#include "types.hpp"

class Memory{
public:
    Memory(double capfactor=1.25);
    void write(regsize_t addr, memunit_t mu);
    memunit_t read(regsize_t addr);
    
private:
    double capfactor_;
    std::vector<memunit_t> mem_;

    void resize();
};

#endif