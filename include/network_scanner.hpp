#ifndef __NETWORK_SCANNER
#define __NETWORK_SCANNER

#include <vector>
#include "host_device.hpp"
#include <winsock2.h>
#include <iphlpapi.h>

class NetworkScanner
{
private:
    std::vector<Device> devices;
    unsigned long subnetMask;
    unsigned long hostIpv4Address;
    void processIpV4(unsigned long ipV4Address, unsigned char* macAddress, unsigned long macAddressLen);
public:
    NetworkScanner() = default;
    NetworkScanner(HostDevice& hostDevice);
    ~NetworkScanner() = default;

    void                scan();
    std::vector<Device> getDevices() const;
};


#endif