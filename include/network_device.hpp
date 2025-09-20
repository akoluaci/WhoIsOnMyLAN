#ifndef NETWORK_DEVICE
#define NETWORK_DEVICE

#include "device.hpp"

class NetworkDevice : public Device
{
private:
    // std::string vendor;
    // std::string hostName; // NetBIOS required. implemented later
public:
    NetworkDevice(/* args */) = default;
    NetworkDevice(unsigned long ipV4Address, unsigned char* macAddress, unsigned long macAddressLength);
    ~NetworkDevice() = default;

    // // std::string getVendor() const;
    // std::string getHostName() const;

    // void setVendor(std::string uoiCode);
    // void setHostName(std::string hostName);

    void printDeviceInformation() const override;
};


#endif