#ifndef SPELL_REGIO_HPP
#define SPELL_REGIO_HPP

#include "io/UniIO.hpp"

class RegIO : public UniIO{
public:
    RegIO() =default;
    int           id() override;
    regsize_t in() override;
    void        out(regsize_t data) override;
    void*       ptr();
    void        setptr(void *ptr);
    
private:
    regsize_t *regp_;
};

#endif