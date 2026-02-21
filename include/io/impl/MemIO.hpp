#ifndef SPELL_MEMIO_HPP
#define SPELL_MEMIO_HPP

#include "io/UniIO.hpp"
#include "io/Memory.hpp"

class MemIO : public UniIO{
public:
    MemIO(charunit_t *unitp);
    int           id() override;
    regsize_t in() override;
    void        out(regsize_t data) override;

private:
    charunit_t *unitp_;
};

#endif