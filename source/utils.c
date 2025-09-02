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

int connection(int address_family, int type, int protocol, unsigned long ipv4_address, int port) 
{
    WSADATA wsa_data = {0};
    int wsa_result = 0;
    SOCKET new_socket = INVALID_SOCKET;
    struct sockaddr_in client_service = {0};
    int result = 0;

    wsa_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (wsa_result != 0) {
        puts("WSAStartup failed");
        return 1;
    }

    new_socket = socket(address_family, type, protocol);

    if (INVALID_SOCKET == new_socket) {
        puts("[ERROR in connection]Socket creation failed!");
        printf("Error code: %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    client_service.sin_family = AF_INET;
    client_service.sin_port = htons(port);
    client_service.sin_addr.s_addr = ipv4_address;

    result = connect(new_socket, (SOCKADDR *) & client_service, sizeof (client_service));
    if (SOCKET_ERROR == result) {
        puts("[ERROR]Socket creation failed!");
        printf("Error Code: %d\n", WSAGetLastError());
        result = closesocket(new_socket);
        // if (result == SOCKET_ERROR) {
        //     puts("[ERROR]Error during closing socket");
        //     printf("Error Code: %d\n", WSAGetLastError());
        // }
        // WSACleanup();
        return -1;
    }
    return 0;
}
