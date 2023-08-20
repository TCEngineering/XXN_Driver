#include <stdint.h>

#define CAN_MAX_DLEN 8

typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned long __u32;

typedef __u32 canid_t;


struct can_frame {
    canid_t can_id;  // 32 bit CAN_ID + EFF/RTR/ERR flags 
    __u8    can_dlc; // frame payload length in byte (0 .. CAN_MAX_DLEN) 
    __u8    data[CAN_MAX_DLEN];
};

struct signal_decode {
    uint32_t signal_frame;
    uint8_t start_byte;
    uint8_t end_byte;
    uint8_t start_bit;
    uint8_t number_of_bits;
};