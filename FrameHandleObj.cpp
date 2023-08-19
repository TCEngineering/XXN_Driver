#include "frameDefs.h"

#include <stdint.h>
#include <stdio.h>



class FrameHandler
{
    public:
        template <size_t RFN, size_t SN>
        FrameHandler(Can_frame (&raw_frames)[RFN], Signal_decode (&signals)[SN])
        : raw_frames{raw_frames}, rf_length{RFN}, signals{signals}, sig_length{SN} {}
        
        struct Can_frame framenull = {0x0, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

        void print_buffer()
        {
            for(int i = 0; i < rf_length; i++)
            {
                printf("%X\t%X\t", raw_frames[i].can_id, raw_frames[i].can_dlc);
                for(int j = 0; j < 8; j++)
                {
                    printf("%X\t", raw_frames[i].data[j]);
                }
                printf("\n");
            }
        }

        void print_signal_template()
        {
            for(int i = 0; i < sig_length; i++)
            {
                printf("%X\t%X\t%X\t%X\t", signals[i].signal_frame, signals[i].start_byte, signals[i].end_byte, signals[i].start_bit, signals[i].number_of_bits);
                printf("\n");
            }
        }


        int frame_wr(struct Can_frame frame)
        //write frame to frames array if id matches one of the entries
        {
            int frame_id = check_id(frame.can_id);
            if (frame_id != -1)
            {
                raw_frames[frame_id] = frame;
            }
            
            return 0;
        }

        struct Can_frame frame_rd(int32_t can_id)
        //return frame with identifyer equal to can_id
        {
            int frame_id = check_id(can_id);
            if (frame_id != -1)
            {
                return raw_frames[frame_id];
            }
            return framenull;        
        }

        uint16_t u16_rd(int signal)
        //return signal of length between 9 and 16 bits
        {
            
            Signal_decode signal_template = signals[signal]; //retrieve decoding template
            Can_frame raw_frame = frame_rd(signal_template.signal_frame); //retrieve frame that contains the signal

            uint32_t signal_raw = raw_frame.data[signal_template.start_byte];

            for(int i = signal_template.start_byte; i < signal_template.end_byte; i++)
            {
                signal_raw = (signal_raw << 8) + raw_frame.data[i+1];
            }
            
            return signal_raw;
        }

    private:

        Can_frame *raw_frames;
        size_t rf_length;
        Signal_decode *signals;
        size_t sig_length;

        int check_id(uint32_t can_id)
        //iterate through frames array and return index of can_id. Return -1 if it is not in the array
        {
            for(int i = 0; i < rf_length; i++)
            {
                if (raw_frames[i].can_id == can_id)
                {
                    return i;
                }
            }
            return -1;
        }
};