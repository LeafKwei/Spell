#ifndef SPELL_REGIO_HPP
#define SPELL_REGIO_HPP

#include "io/UniIO.hpp"
#include "io/Ptrctl.hpp"

class RegIO : public UniIO, public Ptrctl{
public:
    RegIO() =default;
    int           id() override;
    void*       ptr() override;
    void        setptr(void *ptr) override;
    regsize_t in() override;
    void        out(regsize_t data) override;

private:
    regsize_t *regp_;
};

#endif