#include <stdint.h>
#include <stdio.h>


struct can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t  can_dlc; /* Data Length Code (number of data bytes)*/
    uint8_t  data[8];
};


struct can_frame frame0 = {0x5E8, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F};
struct can_frame frame1 = {0x5E9, 8, 0x6C, 0xDB, 0x6C, 0xDB, 0x01, 0xF5, 0x00, 0x96};
struct can_frame frame2 = {0x5EA, 8, 0x7A, 0xAA, 0x03, 0xE8, 0x00, 0x00, 0x6C, 0xDB};
struct can_frame frame3 = {0x5EB, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F};
struct can_frame frame4 = {0x5EC, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F};

struct can_frame frames[] = {frame0, frame1, frame2, frame3, frame4};

struct can_frame frame_buffer0 = {0x5EB, 8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

struct can_frame frame_buffer[] = {frame_buffer0};

int get_frame(struct can_frame frame);
int check_id(uint32_t can_id);
void display_frames();

int main()
{
    display_frames();
    get_frame(frame_buffer0);
    display_frames();

    return 0;
}

int get_frame(struct can_frame frame)
{
    int frame_id = check_id(frame.can_id);
    if (frame_id != -1)
    {
        frames[frame_id] = frame;
    }
    
    return 0;
}

int check_id(uint32_t can_id)
{
    for(int i = 0; i < sizeof(frames)/sizeof(frames[0]); i++)
    {
        if (frames[i].can_id == can_id)
        {
            return i;
        }
    }
    return -1;
}

void display_frames()
{
    for(int i = 0; i < sizeof(frames)/sizeof(frames[0]); i++)
    {
        printf("%X\t", frames[i].can_id);
        for(int j = 0; j < sizeof(frame0.data); j++)
        {
            printf("%X\t", frames[i].data[j]);
        }
        printf("\n");
    }    
}


