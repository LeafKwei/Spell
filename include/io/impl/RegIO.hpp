#ifndef SPELL_REGIO_HPP
#define SPELL_REGIO_HPP

#include "io/UniIO.hpp"
#include "io/Memory.hpp"

class RegIO : public UniIO{
public:
    RegIO(regsize_t *regp);
    int           id() override;
    regsize_t in() override;
    void        out(regsize_t data) override;

private:
    regsize_t *regp_;
};

#endif