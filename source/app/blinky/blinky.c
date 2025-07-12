#include "blinky.h"
#include "gio.h"

void blinky_routine(void) {
    int i;

    gioSetBit(gioPORTB, 1, 1);
    gioSetBit(gioPORTB, 2, 0);

    for (;;) {
        gioToggleBit(gioPORTB, 1);
        gioToggleBit(gioPORTB, 2);
        for (i=0; i<DELAY; i++);
    }
}