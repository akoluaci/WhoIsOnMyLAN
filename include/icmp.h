#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)
struct IcmpHeader
{
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    uint16_t id;
    uint16_t seq;
};
#pragma pack(pop)

uint16_t calculate_checksum(void *data, size_t len);
int send_ping(const char* target_ip_address);

#ifdef __cplusplus
}
#endif

#endif