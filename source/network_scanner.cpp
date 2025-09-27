#include "network_scanner.hpp"
#include "host_device.hpp"
#include "network_device.hpp"
#include "arp.h"
#include "utils.h"
#include "icmp.h"
#include <windows.h>
#include <ws2tcpip.h>
#include <winbase.h>
#include <map>
#include <iostream>
#include <iomanip>

#define MAX_SIZE 255
std::map<int, std::string> port_services;

void initializePortServices() {
    port_services[21]  = "FTP";
    port_services[22]  = "SSH";
    port_services[23]  = "Telnet";
    port_services[25]  = "SMTP";
    port_services[53]  = "DNS";
    port_services[80]  = "HTTP";
    port_services[135] = "Microsoft EPMAP (End Point Mapper)";
    port_services[443] = "HTTPS";
    // Add more ports as needed
}


NetworkScanner::NetworkScanner() {
    unsigned long flags              = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER; 
    unsigned long bufferSize         = 15000;
    unsigned long computerNameLen    = MAX_SIZE;
    char computerName[MAX_SIZE + 1]  = {0};
    char* lpMsgBuf                   = NULL;
    PIP_ADAPTER_ADDRESSES pAddresses = (PIP_ADAPTER_ADDRESSES)malloc(sizeof(PIP_ADAPTER_ADDRESSES) * bufferSize);
    unsigned long result             = 0;
    auto hostDevice = std::make_unique<HostDevice>();

    if (NULL == pAddresses) {
        std::cout << "[ERROR]Not enought memory space for allocation!\n";
        exit(EXIT_FAILURE);
    }

    result = GetComputerNameA(computerName, &computerNameLen);
    if (result == 0) {
        std::cout << "[WARNING]Computer name cannot retrieved!\n";
        hostDevice->setFriendlyName("");
    } else {
        hostDevice->setFriendlyName(computerName);
    }

    result = GetAdaptersAddresses(AF_INET, flags, 0, pAddresses, &bufferSize);

    if (NO_ERROR == result) {
        while (pAddresses->OperStatus != IfOperStatusUp || pAddresses->IfType == IF_TYPE_SOFTWARE_LOOPBACK) {
            pAddresses = pAddresses -> Next;
        }
        
        if (pAddresses != NULL) {
            PIP_ADAPTER_UNICAST_ADDRESS pUnicast = pAddresses->FirstUnicastAddress;
            while (pUnicast)
            {
                if (AF_INET == pUnicast->Address.lpSockaddr->sa_family) {
                    struct sockaddr_in *ipSockAddr = (struct sockaddr_in*)pUnicast->Address.lpSockaddr;
                    hostDevice->setIpv4Address(ipSockAddr->sin_addr.S_un.S_addr);
                    hostIpv4Address = ipSockAddr->sin_addr.S_un.S_addr;
                    uint32_t onLinkPrefixLength = pUnicast->OnLinkPrefixLength;
                    subnetMask = ~((1 << (32 - onLinkPrefixLength)) - 1);
                }
                pUnicast = pUnicast -> Next;
            }
            if (pAddresses->PhysicalAddressLength != 0)
                hostDevice->setMacAddress(pAddresses->PhysicalAddress);
            
            hostDevice->setAdapterName(pAddresses->FriendlyName);
            hostDevice->setDescription(pAddresses->Description);
        }
        devices.push_back(std::move(hostDevice));
    } else {
        std::cout << "Call to GetAdaptersAddresses failed with error: " << result << "\n";
        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
                    NULL, result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   
                    // Default language
                    (LPTSTR) & lpMsgBuf, 0, NULL)) {
                        std::cout << "Error Message: " << std::string(lpMsgBuf) << "\n";
                        LocalFree(lpMsgBuf);
                        if (pAddresses)
                        free(pAddresses);
                        exit(1);
                    }
    }
}

void NetworkScanner::scan() {
    
    uint32_t ipv4Address = ntohl(hostIpv4Address);
    uint32_t subnetMask = this->subnetMask;
    uint32_t networkAddress = subnetMask & ipv4Address;
    // std::cout << "Network Address: " << networkAddress << "\n";

    uint32_t subnetInv = ~subnetMask;
    uint32_t broadcast = networkAddress | subnetInv;
    
    
    uint32_t startIp = networkAddress + 1;
    // in_addr start_addr;
    // start_addr.s_addr = htonl(startIp);
    // char startIpStr[INET_ADDRSTRLEN];
    // inet_ntop(AF_INET, &start_addr, startIpStr, INET_ADDRSTRLEN);
    initializePortServices();
    unsigned char macAddress[6] = {0};
    unsigned long macAddressLen = 6;
    for (uint32_t i = startIp; i < startIp + 255; i++)
    {
        uint32_t startIpNet = htonl(i);
        if (!send_ping(startIpNet)) {
            if (!send_arp_request(startIpNet, macAddress, &macAddressLen)) {
                auto networkDevicePtr = std::make_unique<NetworkDevice>(startIpNet, macAddress, macAddressLen);
                devices.push_back(std::move(networkDevicePtr));
                for (auto it : port_services)
                {
                    int port = it.first;
                    if (!connection(AF_INET, SOCK_STREAM, IPPROTO_TCP, startIpNet, port)) {
                        // networkDevicePtr->addPort(port);    
                        devices.back()->addPort(port);
                        std::cout << devices.back()->getIpv4Address() << "\n";
                        // break; 
                    }
                }
            } else {
                std::cout << "[ERROR]MAC Address cannot be resolved!\n";
                return; 
            }
            
        } /*else {
            std::cout << "[ERROR]Ping request isnt replied.\n";
        }*/
    }
    
}

Device& NetworkScanner::getDevice(size_t index) const {
    if (index < devices.size()) {
        return *devices[index].get();
    }
    throw std::out_of_range("Index is out of range!\n");
}

int NetworkScanner::getDeviceCount() const {
    return devices.size();
}