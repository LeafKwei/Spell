#ifndef SPELL_MEMIO_HPP
#define SPELL_MEMIO_HPP

#include "io/UniIO.hpp"
#include "io/Ptrctl.hpp"
#include "io/Memory.hpp"

class MemIO : public UniIO, public Ptrctl{
public:
    MemIO() =default;
    int           id() override;
    void*       ptr() override;
    void        setptr(void *ptr) override;
    regsize_t in() override;
    void        out(regsize_t data) override;

private:
    charunit_t *unitp_;
};

#endif