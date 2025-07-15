#include "blinky.h"
#include "gio.h"   /* HALCoGen GPIO driver */

void Blinky(void)
{
    int i;
    for (;;)
    {
        gioToggleBit(gioPORTB, 2);  /* LED1 on LaunchPad */
        for (i=0; i<DELAY_BLINKY; i++);
    }
}
