#include "device.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>

Device::Device(unsigned long _ipv4Address, unsigned char* _macAddress, unsigned long _macAddressLength, int port) {
    setIpv4Address(_ipv4Address);
    setMacAddress(_macAddress);
    openPorts.push_back(port);
}

void Device::setIpv4Address(unsigned long _ipv4Address) {
    char ipV4Char[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &_ipv4Address, ipV4Char, INET_ADDRSTRLEN);
    ipv4Address = ipV4Char;
}

void Device::setMacAddress(unsigned char* _macAddress, unsigned long macAddressLength) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    
    for (size_t i = 0; i < macAddressLength; ++i) {
        ss << std::setw(2) << static_cast<int>(_macAddress[i]);
        if (i != macAddressLength - 1)
            ss << ":";
    }
    macAddress = ss.str();
}

void Device::addPort(int port) {
    if (std::find(openPorts.begin(), openPorts.end(), port) == openPorts.end()) {
        openPorts.push_back(port);
    }
}

std::vector<int> Device::getOpenPorts() const {
    return openPorts;
}

std::string Device::getIpv4Address() const {
    return ipv4Address;
}
std::string Device::getMacAddress() const {
    return macAddress;
}