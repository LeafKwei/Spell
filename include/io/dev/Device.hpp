#ifndef SPELL_DEVICE_HPP
#define SPELL_DEVICE_HPP

#include "io/UniIO.hpp"

class Device{
public:
    virtual regsize_t id() const noexcept =0;         /* 获取设备ID */
    virtual UniIO*    portIO(regsize_t port) =0;     /* 获取指定端口号的IO对象 */
};

#endif