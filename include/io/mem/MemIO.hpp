#ifndef SPELL_MEMIO_HPP
#define SPELL_MEMIO_HPP

#include "io/UniIO.hpp"
#include "io/mem/Memory.hpp"

class MemIO : public UniIO{
public:
    MemIO() =default;
    int           id() override;
    regsize_t in() override;
    void        out(regsize_t data) override;
    void*       ptr();
    void        setptr(void *ptr);

private:
    charunit_t *unitp_;
};

#endif