#include "utils.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

SOCKET create_socket(int address_family, int type, int protocol) 
{
    WSADATA wsa_data = {0};
    int wsa_result = 0;
    SOCKET new_socket = INVALID_SOCKET;

    wsa_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (wsa_result != 0) {
        puts("WSAStartup failed");
        return 1;
    }

    new_socket = socket(address_family, type, protocol);
    return new_socket;
}