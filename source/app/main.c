#include "sys_core.h"
#include "gio.h"
#include "rti.h"
#include "blinky.h"
#include "lcd.h"

int main(void)
{
    volatile int i;
    _enable_interrupt_();
    gioInit();
    rtiInit();
    gioSetBit(gioPORTB, 1, 0);
    gioSetBit(gioPORTB, 2, 1);
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);
    rtiStartCounter(rtiCOUNTER_BLOCK0);
    Blinky();
}
