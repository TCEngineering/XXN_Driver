#include <stdint.h>
#include <stdio.h>

struct Can_frame
{
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t  can_dlc; /* Data Length Code (number of data bytes)*/
    uint8_t  data[8];
};

struct Signal_decode
{
    uint32_t signal_frame;
    uint8_t start_byte;
    uint8_t end_byte;
    uint8_t start_bit;
    uint8_t number_of_bits;
};

Can_frame raw_frames[] =
{
    {0x5E8, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F},
    {0x5E9, 8, 0x6C, 0xDB, 0x6C, 0xDB, 0x01, 0xF5, 0x00, 0x96},
    {0x5EA, 8, 0x7A, 0xAA, 0x03, 0xE8, 0x00, 0x00, 0x6C, 0xDB},
    {0x5EB, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F},
    {0x5EC, 8, 0x05, 0xEF, 0x02, 0x0D, 0x06, 0x5D, 0x00, 0x8F}
};

Signal_decode signals[] =
{
    {0x5E8, 0, 1, 0, 16},
    {0x5E8, 2, 3, 0, 16},
    {0x5E8, 4, 5, 0, 16},
    {0x5E8, 6, 7, 0, 16}
};

class FrameHandler{
  public:
    template <size_t RFN, size_t SN>
    FrameHandler(Can_frame (&raw_frames)[RFN], Signal_decode (&signals)[SN])
      : raw_frames{raw_frames}, rf_length{RFN}, signals{signals}, sig_length{SN} {}

    void printcan_ids() 
    {
      for (size_t i = 0; i < rf_length; i++)
      {
        printf("%X", raw_frames[i].can_id);
        printf("\n");
      }
    }

    void print_signals()
    {
      for (size_t i = 0; i < sig_length; i++)
      {
        printf("%X\t", signals[i].signal_frame);
        printf("%X\t", signals[i].start_byte);
        printf("%X\t", signals[i].end_byte);
        printf("\n");
      }
    }

  private:
    Can_frame *raw_frames;
    size_t rf_length;
    Signal_decode *signals;
    size_t sig_length;
};

FrameHandler canTest {raw_frames, signals};

int main()
{
  //Serial.begin(115200);
  //while (!Serial);
  canTest.printcan_ids();
  canTest.print_signals();
  return 0;
}