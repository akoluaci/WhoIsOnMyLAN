#include <Ws2tcpip.h>
#include <stdio.h>
// #include <winsock2.h>
#include "utils.h"
#include "icmp.h"
#include "ip.h"

#pragma comment(lib, "Ws2_32.lib")

uint16_t calculate_checksum(void *data, size_t len)
{
    uint16_t *buffer = (uint16_t*)data;
    uint16_t checksum;
    uint32_t sum = 0;

    while (len > 1)
    {
        sum += *buffer++;
        len -= 2;
    }
    
    if (len == 1)
        sum += *buffer;
    
    while (sum >> 16)
        sum = ((sum & 0xFFFF) + (sum >> 16));
    
    checksum = (uint16_t)~sum;
    return checksum;
}

int send_ping(unsigned long target_ip_address)
{
    struct sockaddr_in recv_addr   = {0};
    struct sockaddr_in sender_addr = {0};
    struct sockaddr_in local_addr  = {0};
    int sender_address_size        = sizeof(sender_addr);
    char received_buffer[2048]     = {0};
    const int buffer_len           = 2048;
    SOCKET socket                  = INVALID_SOCKET;
    int result                     = NO_ERROR;
    struct IcmpHeader icmp = {.code = 0, .type = 8, .checksum = 0, .id = 1, .seq = 1};

    // printf("target_ip_address:%s\n", target_ip_address);
    recv_addr.sin_family = AF_INET;
    // TODO
    // Port must be a parameter value, not static.
    recv_addr.sin_port = htons(0);
    recv_addr.sin_addr.S_un.S_addr = target_ip_address;
    // result = inet_pton(AF_INET, target_ip_address, (void*)&recv_addr.sin_addr);
    // if (result <= 0) {
    //     puts("[ERROR]IP Address cannot be resolved!");
    //     printf("Error Code:%d\n", WSAGetLastError());
    // }

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(0);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socket = create_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (SOCKET_ERROR == socket) {
        puts("Socket creation failed!");
        printf("Error Code:%d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    if (bind(socket, (struct sockaddr*)&local_addr, sizeof(local_addr)) == SOCKET_ERROR) {
        puts("Binding failed!");
        printf("Error Code:%d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    icmp.checksum = calculate_checksum((void*)&icmp, sizeof(icmp));
    result = sendto(socket, (char*)&icmp, sizeof(icmp), 0, (SOCKADDR *) &recv_addr, sizeof(recv_addr));
    if (SOCKET_ERROR == result) {
        puts("Error while sending icmp request!\n");
        printf("Error code:%d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    // puts("Data is sent");
    result = recvfrom(socket, received_buffer, buffer_len, 0, (SOCKADDR *)&sender_addr, &sender_address_size);
    if (SOCKET_ERROR == result) {
        puts("Error while receiving!");
        printf("Error code:%d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    // puts("Data is received");
    shutdown(socket, SD_BOTH);
    closesocket(socket);
    WSACleanup();

    struct IpHeader *ip = (struct IpHeader*)received_buffer;
    unsigned int ip_len = ip -> ihl * 4;
    struct IcmpHeader* ping_result = (struct IcmpHeader*)(received_buffer + ip_len);
    // printf("ping_result -> type: %d\n", ping_result -> type);
    if (ping_result -> type == 0)
        return 0;
    return 1;
}

