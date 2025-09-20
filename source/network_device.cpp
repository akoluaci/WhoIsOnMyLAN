#include "network_device.hpp"
#include <iostream>

NetworkDevice::NetworkDevice(unsigned long ipV4Address, unsigned char* macAddress, unsigned long macAddressLength) 
    : Device(ipV4Address, macAddress, 6, 135) {
        
        // std::string uoiCode = getMacAddress().substr(0, 8);
        // setVendor(uoiCode);
    // hostName = _hostName;
}


// std::string NetworkDevice::getVendor() const {
//     return vendor;
// }

/*std::string NetworkDevice::getHostName() const {
    return getHostName;
}*/

// void NetworkDevice::setVendor(std::string uoiCode) {
//     // vendor = _vendor;
//     vendor = getVendorName(uoiCode);
// }

void NetworkDevice::printDeviceInformation() const {
    // std::cout << "Host Name: " << hostName << "\n";
    std::cout << "Vendor: " << getVendor() << "\n"
              << "IpV4Address: " << getIpv4Address() << "\n" 
              << "MacAddress : " << getMacAddress() << "\n";

    std::vector<int> openPorts = getOpenPorts();
    
    std::cout << "Ports: ";
    for (int port : openPorts)
        std::cout << port << " ";
    std::cout << "\n";
}