#ifndef __NETWORK_SCANNER
#define __NETWORK_SCANNER

#include <vector>
#include <winsock2.h>
#include <iphlpapi.h>
#include <memory>
#include "device.hpp"
#include <functional>
#include <atomic>

class NetworkScanner
{
private:
    std::vector<std::unique_ptr<Device>> devices;
    unsigned long subnetMask;
    unsigned long hostIpv4Address;
    void processIpV4(unsigned long ipV4Address, unsigned char* macAddress, unsigned long macAddressLen);
    std::atomic<bool> stopRequest = true;
public:
    NetworkScanner() = default;
    ~NetworkScanner() = default;

    void                scan();
    void getHostDevice(/*std::function<void(const std::string& ip, const std::string& mac)> onDeviceFoundCallback*/);
    Device& getDevice(size_t index) const;
    int getDeviceCount() const;
    const std::vector<std::unique_ptr<Device>>& getDevices() const;
    std::vector<const Device*> getDevicePointers() const;
    void setStopRequest(std::atomic<bool> _stopRequest);
    std::atomic<bool> getStopRequest() const;
};


#endif