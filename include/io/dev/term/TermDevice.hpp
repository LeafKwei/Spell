#ifndef SPELL_TERMDEVICE_HPP
#define SPELL_TERMDEVICE_HPP

#include "io/dev/Device.hpp"
#include "io/dev/term/TermDeviceIO.hpp"

class TermDevice : public Device{
public:
    regsize_t id() const noexcept override;
    UniIO*    portIO(regsize_t port) override;
private:
    TermDeviceIO termio_;
};

#endif