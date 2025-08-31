#ifndef HOST_DEVICE_HPP
#define HOST_DEVICE_HPP

#include "device.hpp"
#include <ws2tcpip.h>
class HostDevice : public Device
{
private:
    std::string adapterName;
    std::string friendlyName;
    std::string description;
public:
    HostDevice(/* args */) = default;
    HostDevice::HostDevice(PWCHAR _adapterName, PWCHAR _description, std::string _friendlyName);
    ~HostDevice() = default;

    std::string getAdapterName()  const;
    std::string getFriendlyName() const;
    std::string getDescription()  const;

    void setFriendlyName(std::string friendlyName);
    void setAdapterName(PWCHAR adapterName);
    void setDescription(PWCHAR description);

    void printDeviceInformation() const override;

};

#endif