#include "rti.h"
#include "gio.h"

#define DELAY_PERIOD_MS     500

volatile uint32_t rti_counter = 0;

void rtiNotification(uint32 notification)
{
    rti_counter++;

        if (rti_counter >= DELAY_PERIOD_MS)  // 500 ms blink period (LED toggles every 0.5s)
        {
            gioToggleBit(gioPORTB, 1);
            rti_counter = 0;
        }
}
