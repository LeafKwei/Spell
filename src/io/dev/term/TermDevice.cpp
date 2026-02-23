#include "def/dev.hpp"
#include "io/dev/term/TermDevice.hpp"

regsize_t TermDevice::id() const noexcept{
    return DEV_ID_TERM;
}

UniIO* TermDevice::portIO(regsize_t port){
    termio_.setport(port);
    return &termio_;
}