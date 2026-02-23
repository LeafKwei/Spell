#ifndef SPELL_DEVICEBUS_HPP
#define SPELL_DEVICEBUS_HPP

#include <unordered_map>
#include <memory>
#include "def/types.hpp"
#include "def/config.hpp"
#include "io/dev/Device.hpp"
#include "io/dev/bad/BadDevice.hpp"

class DeviceBus{
public:
    using Bus_t = int;
    using DevicePtr = std::shared_ptr<Device>;
    using DeviceMap = std::unordered_map<Bus_t, DevicePtr>;

public:
    regsize_t  attachDevice(Device *devp, regsize_t firstPort, regsize_t lastPort);  /* 挂载设备到firstPort到lastPort(包含)之间的端口上，当portIO函数接收到此范围内的端口时，将交由该设备处理。挂载成功时返回该设备的ID，设备的端口不可重叠 */
    UniIO*     portIO(regsize_t port); /* 获取端口对应的IO对象 */

private:
    DeviceMap devices_;
    BadDevice  baddevice_;

private:
    int             insertDevice(Device *devp, Bus_t bus);
    DevicePtr findDevice(regsize_t port);
    Bus_t        port2bus(regsize_t port) const noexcept;
};

inline DeviceBus::Bus_t  DeviceBus::port2bus(regsize_t port) const noexcept{
    return static_cast<Bus_t>(port / PORT_BLOCK_SIZE);
}

#endif