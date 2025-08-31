#ifndef DEVICE_H
#define DEVICE_H

#include <vector>
#include <string>

class Device
{
private:
    // std::string      name;
    // std::string      description;
    std::string      ipv4Address;
    std::string      macAddress;
    std::vector<int> openPorts;
public:
    Device() = default;
    Device(unsigned long ipv4_address, unsigned char* mac_address, unsigned long _macAddressLength, int port);
    ~Device() = default;

    
    void setIpv4Address(unsigned long ipv4Address);
    void setMacAddress(unsigned char* _macAddress, unsigned long macAddressLength = 6);
    void addPort(int port);

    std::string      getIpv4Address() const;
    std::string      getMacAddress() const;
    std::vector<int> getOpenPorts() const;

    virtual void printDeviceInformation() const = 0;
};



#endif