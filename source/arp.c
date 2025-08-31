#include "arp.h"
#include <ws2tcpip.h>
#include <winsock.h>
#include <iphlpapi.h>
#include <stdio.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

// TODO
// Add source ip address
int send_arp_request(const char* target_ip_address, unsigned char* mac_address, unsigned long* mac_address_len)
{
    // long mac_address[2];
    // long mac_address_len = 6;
    // IPAddr dest_ip = inet_addr(target_ip_address);
    struct sockaddr_in ipAddr = {0};
    int result = inet_pton(AF_INET, target_ip_address, (void*)&ipAddr.sin_addr);
    if (result <= 0) {
        puts("[ERROR]IP Address cannot be resolved!");
        printf("Error Code:%d\n", WSAGetLastError());
    }
    // puts("Ip is solved");
    long dw_result = SendARP(ipAddr.sin_addr.s_addr, 0, (void*)mac_address, mac_address_len);
    // printf("dw_result:%ld\n", dw_result);
    if (NO_ERROR == dw_result)
        return 0;
    return 1;

}