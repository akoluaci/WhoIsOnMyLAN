#include "network_device.hpp"
#include <iostream>
NetworkDevice::NetworkDevice(std::string _vendor/*, std::string _hostName*/) {
    vendor = _vendor;
    // hostName = _hostName;
}

std::string NetworkDevice::getVendor() const {
    return vendor;
}

/*std::string NetworkDevice::getHostName() const {
    return getHostName;
}*/

void NetworkDevice::setVendor(std::string _vendor) {
    vendor = _vendor;
}

void NetworkDevice::printDeviceInformation() const {
    // std::cout << "Host Name: " << hostName << "\n";
    std::cout << "Vendor: " << vendor << "\n";
}