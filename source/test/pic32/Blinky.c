#include <xc.h>

#pragma config FNOSC = FRCPLL       // Internal Fast RC oscillator (8 MHz) w/ PLL
#pragma config FPLLIDIV = DIV_2     // Divide FRC before PLL (now 4 MHz)
#pragma config FPLLMUL = MUL_20     // PLL Multiply (now 80 MHz)
#pragma config FPLLODIV = DIV_2     // Divide After PLL (now 40 MHz) see figure 8.1 in datasheet for more info
#pragma config FWDTEN = OFF         // Watchdog Timer Disabled

// Defines
#define SYSCLK 40000000L

void main (void)
{
	volatile unsigned long t=0;
	
	DDPCON = 0;
	
	TRISBbits.TRISB6 = 0;
	LATBbits.LATB6 = 0;	
	INTCONbits.MVEC = 1;

	while (1)
	{
		t++;
		if(t==500000)
		{
			t = 0;
			LATBbits.LATB6 = !LATBbits.LATB6; // Blink led on RB6
		}
	}

}

