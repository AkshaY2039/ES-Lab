/*
	Exercise 1.1 : Toggle LED connected to PD3 and PD0.
					Observe the waveforms in debug mode and calculate on time, off time and frequency.
*/

// LaunchPad built-in hardware
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad

#include "..\..\TM4C_Common\tm4c123gh6pm.h"

#define second 1454480 //1 second = 1454480

/*Function for Initializing Port D*/
void PortD_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000008;		// 1) activate clock for Port D
	delay = SYSCTL_RCGC2_R;				// allow time for clock to start
	// only PF0 needs to be unlocked, other bits can't be locked
	GPIO_PORTD_AMSEL_R &= ~0x00;		// 3) disable analog on PD
	GPIO_PORTD_PCTL_R = 0x00000000;		// 4) PCTL GPIO on PD
	GPIO_PORTD_DIR_R |= 0x09;			// 5) PD30, PD3 as output
	GPIO_PORTD_AFSEL_R &= ~0x09;		// 6) disable alt funct on PD0, PD3
	GPIO_PORTD_DEN_R = 0x09;			// 7) enable digital I/O on PD0, PD3
}

/*delay function*/
void Delay(void)
{
	unsigned long volatile time;
	time = second;
	while(time)
		time--;
}

/*main function*/
int main(void)
{
	PortD_Init(); //Port D Initialziation
	while(1)
	{
		GPIO_PORTD_DATA_R = 0x08; //Turning only PD3 ON
		Delay(); //Delay
		GPIO_PORTD_DATA_R = 0x01; //Turning only PD0 ON
		Delay(); //Delay
	}
}
