#ifndef IP_H
#define IP_H

#include <stdint.h>

#pragma pack(push, 1)
struct IpHeader
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t ihl:4,
            version: 4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    uint8_t version: 4,
            ihl:4;
#else
# error "Please define __BYTE_ORDER parameter"
#endif
    uint8_t tos;
    uint16_t total_len;
    uint16_t identification;
    uint8_t flags;
    uint16_t fragment_offset;
    uint8_t ttl; // time-to-live
    uint8_t protocol;
    uint16_t header_checksum;
    uint32_t source_address;
    uint32_t destination_address;
};
#pragma pack(pop)

#endif