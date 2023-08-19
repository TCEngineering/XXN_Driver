#include <stdint.h>

struct Can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t  can_dlc; /* Data Length Code (number of data bytes)*/
    uint8_t  data[8];
};

struct Signal_decode {
    uint32_t signal_frame;
    uint8_t start_byte;
    uint8_t end_byte;
    uint8_t start_bit;
    uint8_t number_of_bits;
};