#include <stdint.h>
#include <stdio.h>

struct Can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t  can_dlc; /* Data Length Code (number of data bytes)*/
    uint8_t  data[8];
};

struct Can_frame frames[] =
{
    {0x5E8, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F},
    {0x5E9, 8, 0x6C, 0xDB, 0x6C, 0xDB, 0x01, 0xF5, 0x00, 0x96},
    {0x5EA, 8, 0x7A, 0xAA, 0x03, 0xE8, 0x00, 0x00, 0x6C, 0xDB},
    {0x5EB, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F},
    {0x5EC, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F}
};

class FrameHandler
{
    public:
        template <size_t N>
        FrameHandler(Can_frame (&frames)[N])
            : frames(frames), length(N) {}

        void print_buffer()
        {
            for(int i = 0; i < length; i++)
            {
                printf("%X\t%X\t", frames[i].can_id, frames[i].can_dlc);
                for(int j = 0; j < 8; j++)
                {
                    printf("%X\t", frames[i].data[j]);
                }
                printf("\n");
            }
        }
    private:

        Can_frame *frames;
        size_t length;
};

int main()
{
    FrameHandler can0 = frames;

    can0.print_buffer();
    return 0;
}
