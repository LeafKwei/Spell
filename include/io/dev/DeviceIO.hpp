#ifndef SPELL_DEVICEIO_HPP
#define SPELL_DEVICEIO_HPP

#include "io/UniIO.hpp"

class DeviceIO : public UniIO{
public:
    virtual ~DeviceIO() =default;
    int id() override { return UNIIO_ID_DEV; }
};

#endif