#ifndef SPELL_BADDEVICEIO_HPP
#define SPELL_BADDEVICEIO_HPP

#include "io/UniIO.hpp"

/* 仅作接口兼容使用，不提供任何实际功能 */
class BadDeviceIO : public UniIO{
public:
    BadDeviceIO() =default;
    int           id() override { return UNIIO_ID_BAD; }
    regsize_t in() override { return 0;}
    void        out(regsize_t data) override {}
};

#endif