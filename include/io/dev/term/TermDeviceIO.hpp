#ifndef SPELL_TERMDEVICEIO_HPP
#define SPELL_TERMDEVICEIO_HPP

#include "io/dev/DeviceIO.hpp"

class TermDeviceIO : public DeviceIO{
public:
    TermDeviceIO() =default;
    regsize_t in() override;
    void        out(regsize_t data) override;
    void        setport(regsize_t port);

private:
    void *stream_;
    regsize_t port_;
};

#endif