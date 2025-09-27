#include <iostream>
#include "network_scanner.hpp"
#include "host_device.hpp"
#include "network_device.hpp"
#define SIZE 15000

int main(int argc, char const *argv[])
{
    // HostDevice hostDevice;
    
    NetworkScanner networkScanner;
    Device& dev = networkScanner.getDevice(0);

    try
    {
        HostDevice& hostDevice = dynamic_cast<HostDevice&>(dev);
        hostDevice.printDeviceInformation();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    networkScanner.scan();
    
    int deviceCount = networkScanner.getDeviceCount();
    // std::cout << "Device Count: " << deviceCount << "\n";
    
    for (int i = 1; i < deviceCount; ++i) {
        Device& dev1 = networkScanner.getDevice(i);
        try
        {
            NetworkDevice& networkDevice = dynamic_cast<NetworkDevice&>(dev1);
            networkDevice.printDeviceInformation();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }    
    return 0;
}
