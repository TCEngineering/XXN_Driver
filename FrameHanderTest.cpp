#include "FrameHandleObj.cpp"
#include "node_speedo_header.h"

#include <stdio.h>

struct Can_frame frame_buffer0 = {0x5EA, 8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

FrameHandler can0 {frames_init, signals};

int main()
{
    can0.print_buffer();
    can0.print_signal_template();

    can0.frame_wr(frame_buffer0);

    uint16_t latest_map = can0.u16_rd(map);
    uint16_t latest_rpm = can0.u16_rd(rpm);
    uint16_t latest_clt = can0.u16_rd(clt);
    uint16_t latest_tps = can0.u16_rd(tps);

    printf("MAP = %u\n", latest_map);
    printf("RPM = %u\n", latest_rpm);
    printf("CLT = %u\n", latest_clt);
    printf("TPS = %u\n", latest_tps);

    return 0;
}
