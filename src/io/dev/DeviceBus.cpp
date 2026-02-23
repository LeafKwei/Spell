#include "def/dev.hpp"
#include "io/dev/DeviceBus.hpp"

regsize_t DeviceBus::attachDevice(Device *devp, regsize_t firstPort, regsize_t lastPort){
    auto start = firstPort;
    
    /* 遍历指定的端口范围，计算端口对应的总线编号，为每个编号都insert一个该设备的指针 */
    while(start <= lastPort){
        auto bus = port2bus(start);
        if(insertDevice(devp, bus)){
            return -1;
        }
        start += PORT_BLOCK_SIZE;
    }

    return devp -> id();
}

int DeviceBus::insertDevice(Device *devp, Bus_t bus){
    if(devices_.find(bus) != devices_.end()){
        return -1;
    }

    devices_.insert({bus, DevicePtr(devp)});
    return 0;
}

UniIO* DeviceBus::portIO(regsize_t port){
    auto devp = findDevice(port2bus(port));
    return (devp != nullptr) ? devp -> portIO(port) : baddevice_.portIO(port);
}

DeviceBus::DevicePtr DeviceBus::findDevice(regsize_t port){
    auto devp = devices_.find(port2bus(port));
    return (devp != devices_.end()) ? devp -> second : nullptr;
}