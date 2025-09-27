#ifndef __NETWORK_SCANNER
#define __NETWORK_SCANNER

#include <vector>
#include <winsock2.h>
#include <iphlpapi.h>
#include <memory>
#include "device.hpp"

class NetworkScanner
{
private:
    std::vector<std::unique_ptr<Device>> devices;
    unsigned long subnetMask;
    unsigned long hostIpv4Address;
    void processIpV4(unsigned long ipV4Address, unsigned char* macAddress, unsigned long macAddressLen);
public:
    NetworkScanner();
    ~NetworkScanner() = default;

    void                scan();
    Device& getDevice(size_t index) const;
    int getDeviceCount() const;
};


#endif