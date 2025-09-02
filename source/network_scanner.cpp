#include "network_scanner.hpp"
#include <iostream>
#include <windows.h>
#include <ws2tcpip.h>
#include <winbase.h>
#include <iomanip>
#include <stdint.h>
#include "icmp.h"
#include "arp.h"
#include <map>
#include "utils.h"

#define MAX_SIZE 255
std::map<int, std::string> port_services;
void initializePortServices() {
    port_services[21] = "FTP";
    port_services[22] = "SSH";
    port_services[23] = "Telnet";
    port_services[25] = "SMTP";
    port_services[53] = "DNS";
    port_services[80] = "HTTP";
    port_services[135] = "Microsoft EPMAP (End Point Mapper)";
    port_services[443] = "HTTPS";
    // Add more ports as needed
}


NetworkScanner::NetworkScanner(HostDevice& hostDevice) {
    unsigned long flags              = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER; 
    unsigned long bufferSize         = 15000;
    unsigned long computerNameLen    = MAX_SIZE;
    char computerName[MAX_SIZE + 1]  = {0};
    char* lpMsgBuf                   = NULL;
    PIP_ADAPTER_ADDRESSES pAddresses = (PIP_ADAPTER_ADDRESSES)malloc(sizeof(PIP_ADAPTER_ADDRESSES) * bufferSize);
    unsigned long result             = 0;

    if (NULL == pAddresses) {
        std::cout << "[ERROR]Not enought memory space for allocation!\n";
        exit(EXIT_FAILURE);
    }

    result = GetComputerNameA(computerName, &computerNameLen);
    if (result == 0) {
        std::cout << "[WARNING]Computer name cannot retrieved!\n";
        hostDevice.setFriendlyName("");
    } else {
        hostDevice.setFriendlyName(computerName);
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
                    hostDevice.setIpv4Address(ipSockAddr->sin_addr.S_un.S_addr);
                    hostIpv4Address = ipSockAddr->sin_addr.S_un.S_addr;
                    uint32_t onLinkPrefixLength = pUnicast->OnLinkPrefixLength;
                    subnetMask = ~((1 << (32 - onLinkPrefixLength)) - 1);
                    break;
                }
                pUnicast = pUnicast -> Next;
            }
            if (pAddresses->PhysicalAddressLength != 0)
                hostDevice.setMacAddress(pAddresses->PhysicalAddress);
            
            hostDevice.setAdapterName(pAddresses->FriendlyName);
            hostDevice.setDescription(pAddresses->Description);
        }
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
    // std::cout << "\nscan is starting...\n";
    
    uint32_t ipv4Address = ntohl(hostIpv4Address);
    uint32_t subnetMask = this->subnetMask;
    uint32_t networkAddress = subnetMask & ipv4Address;
    // std::cout << "Network Address: " << networkAddress << "\n";

    uint32_t subnetInv = ~subnetMask;
    uint32_t broadcast = networkAddress | subnetInv;
    
    
    // uint32_t startIp = networkAddress + 1;
    // in_addr start_addr;
    // start_addr.s_addr = htonl(startIp);
    // char startIpStr[INET_ADDRSTRLEN];
    // inet_ntop(AF_INET, &start_addr, startIpStr, INET_ADDRSTRLEN);
    initializePortServices();
    unsigned char macAddress[6] = {0};
    unsigned long macAddressLen = 6;
    if (!send_ping(hostIpv4Address)) {
        if (!send_arp_request(hostIpv4Address, macAddress, &macAddressLen)) {
            for (size_t i = 0; i < 6; i++)
            {
                std::cout << std::uppercase << std::hex << std::setw(2) << static_cast<int>(macAddress[i]);
                if (i != 5)
                    std::cout << ":";
            }
        } else {
            std::cout << "[ERROR]MAC Address cannot be resolved!\n";
            return; 
        }
        for (auto it : port_services)
        {
            if (!connection(AF_INET, SOCK_STREAM, IPPROTO_TCP, hostIpv4Address, it.first)) {
                std::cout << it.second << "[Port:" << it.first << "] is used\n";
                break; 
            }
        }
    } else {
        std::cout << "[ERROR]Ping request isnt replied.\n";
    }
    
}
