#include <iostream>
#include "network_scanner.hpp"

#define SIZE 15000

int main(int argc, char const *argv[])
{
    HostDevice hostDevice;
    
    NetworkScanner networkScanner(hostDevice);
    
    // std::cout << "Description: " << hostDevice.getDescription() << "\n" 
            //   << "hostDevice Name: " << hostDevice.getFriendlyName() << "\n" 
            //   << "hostDevice AdapterName: " << hostDevice.getAdapterName() << "\n" 
            //   << "IpV4Address: " << hostDevice.getIpv4Address() << "\n" 
            //   << "MacAddress : " << hostDevice.getMacAddress() << "\n";
    

    networkScanner.scan();
    
    return 0;
}
