#include "device.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>

Device::Device(unsigned long _ipv4Address, unsigned char* _macAddress, unsigned long _macAddressLength, int port) {
    setIpv4Address(_ipv4Address);
    setMacAddress(_macAddress);
    setVendorNameByMacAddress();
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

void Device::setVendor() {
    // vendor = _vendor;
    setVendorNameByMacAddress();
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

std::string Device::getVendor() const {
    return vendor;
}

void Device::setVendorNameByMacAddress() {
    std::string line;    
    int pos = -1;
    int posEnd = -1;

    std::fstream fin("mac-vendors-export.csv", std::ios::in);
    std::string uoiCode = getMacAddress().substr(0, 8);
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
    vendor = vendorName;
}