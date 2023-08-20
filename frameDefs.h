#include <stdint.h>

typedef unsigned long __u32;
typedef __u32 canid_t;

struct can_frame {
    canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t  can_dlc; /* Data Length Code (number of data bytes)*/
    uint8_t  data[8];
};

struct signal_decode {
    uint32_t signal_frame;
    uint8_t start_byte;
    uint8_t end_byte;
    uint8_t start_bit;
    uint8_t number_of_bits;
};