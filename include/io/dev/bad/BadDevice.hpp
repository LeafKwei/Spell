#ifndef SPELL_BADDEVICE_HPP
#define SPELL_BADDEVICE_HPP

#include "def/dev.hpp"
#include "io/dev/Device.hpp"
#include "io/dev/bad/BadDeviceIO.hpp"

class BadDevice : public Device{
public:
    regsize_t id() const noexcept override;
    UniIO*    portIO(regsize_t port) override;
private:
    BadDeviceIO defaultio_;
};

inline regsize_t BadDevice::id() const noexcept{
    return DEV_ID_BAD;
}

inline UniIO* BadDevice::portIO(regsize_t port){
    return &defaultio_;
}

#endif