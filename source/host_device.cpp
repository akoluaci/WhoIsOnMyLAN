#include "host_device.hpp"
#include <iostream>

HostDevice::HostDevice(PWCHAR _adapterName, PWCHAR _description, std::string _friendlyName) {
    setAdapterName(_adapterName);
    setDescription(_description);
    friendlyName = _friendlyName;
}


std::string HostDevice::getAdapterName()  const {
    return adapterName;
};

std::string HostDevice::getFriendlyName() const {
    return friendlyName;
};

std::string HostDevice::getDescription()  const {
    return description;
};

void HostDevice::setAdapterName(PWCHAR _adapterName) {
    std::wstring ws(_adapterName);
    adapterName = std::string(ws.begin(), ws.end());
}

void HostDevice::setDescription(PWCHAR _description) {
    std::wstring ws(_description);
    description = std::string(ws.begin(), ws.end());
}

void HostDevice::setFriendlyName(std::string _friendlyName) {
    friendlyName = _friendlyName;
}

void HostDevice::printDeviceInformation() const {
    std::cout << "Description: " << description << "\n" 
              << "Device Name: " << friendlyName << "\n"
              << "IpV4Address: " << getIpv4Address() << "\n" 
              << "MacAddress : " << getMacAddress() << "\n";
}