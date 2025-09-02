#ifndef ARP_H
#define ARP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)
struct ArpHeader
{
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t  hardware_length;
    uint8_t  protocol_length;
    uint16_t op_code;
    uint8_t  sender_hardware_address[6];
    uint8_t  sender_protocol_address[4];
    uint8_t  target_hardware_address[6];
    uint8_t  target_protocol_address[4];
};
#pragma pack(pop)

int send_arp_request(unsigned long target_ip_address, unsigned char* mac_address, unsigned long* mac_address_len);

#ifdef __cplusplus
}
#endif

#endif

