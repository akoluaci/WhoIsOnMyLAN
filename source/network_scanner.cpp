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
#include "utils.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <iostream>
#include <iomanip>

#define MAX_SIZE 255

class MyThreadPool {
public:
    MyThreadPool(int threadNum = std::thread::hardware_concurrency()) {
        for (size_t i = 0; i < threadNum; ++i)
        {
            stop = false;
            threads.emplace_back([this, i] {
                while (true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        conditionalVar.wait(lock, [this] {
                            return (!tasks.empty() || stop);
                        });
                        if (stop && tasks.empty())
                            return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    // cout_mtx.lock();
                    // std::cout << "Thread [" << std::this_thread::get_id() << "] is executing task " << i << ".\n";
                    // cout_mtx.unlock();
                    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    task();
                }
            });
        }   
    }

    void enqueue(std::function<void()> task)
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(task);
        conditionalVar.notify_one();
    }

    ~MyThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }
        conditionalVar.notify_all();
        for (auto &th : threads)
        {
            if (th.joinable())
                th.join();
        }
        
    }
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable conditionalVar;
    bool stop = false;
};


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


void NetworkScanner::processIpV4(unsigned long ipV4Address, unsigned char* macAddress, unsigned long macAddressLen) {
    if (!send_ping(ipV4Address)) {
        if (!send_arp_request(ipV4Address, macAddress, &macAddressLen)) {
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
            if (!connection(AF_INET, SOCK_STREAM, IPPROTO_TCP, ipV4Address, it.first)) {
                std::cout << it.second << "[Port:" << it.first << "] is used\n";
                break; 

            }
            
        } /*else {
            std::cout << "[ERROR]Ping request isnt replied.\n";
        }*/
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
    
    
    uint32_t startIp = networkAddress + 1;
    // in_addr start_addr;
    // start_addr.s_addr = htonl(startIp);
    // char startIpStr[INET_ADDRSTRLEN];
    // inet_ntop(AF_INET, &start_addr, startIpStr, INET_ADDRSTRLEN);
    initializePortServices();
    
    MyThreadPool myThreadPool(2);
    for (uint32_t i = startIp; i < startIp + 5; i++)
    {
        myThreadPool.enqueue([this, i] {
            std::cout << "ThreadId: " << std::this_thread::get_id() << " is working.\n";
            unsigned char macAddress[6] = {0};
            unsigned long macAddressLen = 6;
            processIpV4(i, macAddress, macAddressLen);
            std::cout << "ThreadId: " << std::this_thread::get_id() << " finished its job.\n";
        });
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