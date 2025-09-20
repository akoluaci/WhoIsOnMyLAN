#include <iostream>
#include "network_scanner.hpp"
#include "host_device.hpp"
#include "network_device.hpp"


int main(int argc, char const *argv[])
{
    // HostDevice hostDevice;
    
    NetworkScanner networkScanner;
    networkScanner.getHostDevice();
    Device& dev = networkScanner.getDevice(0);
    try
    {
        HostDevice& hostDevice = dynamic_cast<HostDevice&>(dev);
        std::cout << "Host Device Information:\n";
        hostDevice.printDeviceInformation();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    networkScanner.scan();
    
    int deviceCount = networkScanner.getDeviceCount();
    std::cout << "\n----------------\nDevices in the network:\n";
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
    std::cout << "\n " << deviceCount << " device(s) found in the network.\n";
    return 0;
}
