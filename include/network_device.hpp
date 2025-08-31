#ifndef NETWORK_DEVICE
#define NETWORK_DEVICE

#include "device.hpp"

class NetworkDevice : public Device
{
private:
    std::string vendor;
    // std::string hostName; // NetBIOS required. implemented later
public:
    NetworkDevice(/* args */) = default;
    NetworkDevice(std::string vendor/*, std::string hostName*/);
    ~NetworkDevice();

    std::string getVendor() const;
    // std::string getHostName() const;

    void setVendor(std::string vendor);
    // void setHostName(std::string hostName);

    void printDeviceInformation() const override;
};


#endif