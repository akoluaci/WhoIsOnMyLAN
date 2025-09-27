#include "network_device.hpp"
#include <iostream>
#include <fstream>


static std::string getVendorName(std::string uoiCode) {
    std::string line;    
    int pos = -1;
    int posEnd = -1;

    std::fstream fin("mac-vendors-export.csv", std::ios::in);

    while (std::getline(fin, line))
    {
        pos = line.find(',');
        std::string oui = line.substr(0, pos);
        if (!oui.compare(uoiCode))
            break;
        line.clear();
    }

    fin.close();
    pos = line.find(',', pos);
    if (line.find('"', pos) != std::string::npos) {
        posEnd = line.rfind('"');
        pos += 2;
    } else {
        posEnd = line.find(',' , pos + 1);
        pos += 1;
    }
    
    std::string vendorName = line.substr(pos, posEnd - pos);
    if (vendorName.empty())
        vendorName.assign("Vendor hides its name from public list");
    return vendorName;
}


NetworkDevice::NetworkDevice(unsigned long ipV4Address, unsigned char* macAddress, unsigned long macAddressLength) 
    : Device(ipV4Address, macAddress, 6, 135) {
    
        std::string uoiCode = getMacAddress().substr(0, 8);
        setVendor(uoiCode);
    // hostName = _hostName;
}


std::string NetworkDevice::getVendor() const {
    return vendor;
}

/*std::string NetworkDevice::getHostName() const {
    return getHostName;
}*/

void NetworkDevice::setVendor(std::string uoiCode) {
    // vendor = _vendor;
    vendor = getVendorName(uoiCode);
}

void NetworkDevice::printDeviceInformation() const {
    // std::cout << "Host Name: " << hostName << "\n";
    std::cout << "Vendor: " << vendor << "\n"
              << "IpV4Address: " << getIpv4Address() << "\n" 
              << "MacAddress : " << getMacAddress() << "\n";

    std::vector<int> openPorts = getOpenPorts();
    
    std::cout << "Ports: ";
    for (int port : openPorts)
        std::cout << port << " ";
    std::cout << "\n";
}