/*
	Exercise 4.1 : Interface a DC motor and control direction using on board switches.

		Using PortA5,A6 for inputs of DC motor i.e. outputs from Tiva Board.
		L293D motor driver
		SW1 left switch is negative logic PF4 on the Launchpad (Using for Anti-Clockwise) --> PA5
		SW2 right switch is negative logic PF0 on the Launchpad (Using for Clockwise) --> PA6
*/

#include "..\..\..\TM4C_Common\tm4c123gh6pm.h"

/*Function for Initializing Port F*/
void PortF_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;		// 1) activate clock for Port F
	delay = SYSCTL_RCGC2_R;				// allow time for clock to start
	GPIO_PORTF_LOCK_R = 0x4C4F434B;		// 2) unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x1F;				// allow changes to PF4-0
	// only PF0 needs to be unlocked, other bits can't be locked
	GPIO_PORTF_AMSEL_R = 0x00;			// 3) disable analog on PF
	GPIO_PORTF_PCTL_R = 0x00000000;		// 4) PCTL GPIO on PF4-0
	GPIO_PORTF_DIR_R = 0x0E;			// 5) PF4,PF0 in, PF3-1 out
	GPIO_PORTF_AFSEL_R = 0x00;			// 6) disable alt funct on PF7-0
	GPIO_PORTF_PUR_R = 0x11;			// enable pull-up on PF0 and PF4
	GPIO_PORTF_DEN_R = 0x1F;			// 7) enable digital I/O on PF4-0
}

/*Function for Initializing Port A*/
void PortA_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000001;		// 1) activate clock for Port A
	delay = SYSCTL_RCGC2_R;				// allow time for clock to start
	GPIO_PORTA_AMSEL_R &= ~0x00;		// 3) disable analog on PA
	GPIO_PORTA_PCTL_R = 0x00000000;		// 4) PCTL GPIO on PA
	GPIO_PORTA_DIR_R |= 0x60;			// 5) PA5, PA6 as output
	GPIO_PORTA_AFSEL_R &= ~0x60;		// 6) disable alt funct on PA5, PA6
	GPIO_PORTA_DEN_R = 0x60;			// 7) enable digital I/O on PA5, PA6
}

/*main function*/
int main(void)
{
	PortF_Init(); //Port F Initialziation
	PortA_Init(); //Port A Initialziation

	/*Controling PA5 with SW1 & PA6 with SW2*/
	while(1)
	{
		if((GPIO_PORTF_DATA_R & 0x11) == 0x01) //if SW1 is Pressed
		{
			GPIO_PORTA_DATA_R = 0x20; //PA5 to be turned ON
		}

		if((GPIO_PORTF_DATA_R & 0x11)  == 0x10) //if SW2 is Pressed
		{
			GPIO_PORTA_DATA_R = 0x40; //PA6 to be turned ON
		}
	}
}
