#ifndef UTILS_C
#define UTILS_C

#include <winsock2.h>
#ifdef __cplusplus
extern "C" {
#endif

SOCKET create_socket(int addressFamily, int type, int protocol);
int connection(int address_family, int type, int protocol, unsigned long ipv4_address, int port);

#ifdef __cplusplus
}
#endif

#endif