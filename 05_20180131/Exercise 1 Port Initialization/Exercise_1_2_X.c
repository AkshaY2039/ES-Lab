/*
	Exercise 1.2_X : Use on board SW1 and SW2 to control LED on PD3 and PD0. 
					Observe the waveforms in debug mode.

	SW1 --> LED on PD0
	SW2 --> LED on PD3
	SW1 & SW2 --> LED on PD0 and PD3 both ON
	No Switch NO LED

	SW2 right switch is negative logic PF0 on the Launchpad
	RED LED connected to PF1 on the Launchpad
	BLUE LED connected to PF2 on the Launchpad
	GREEN LED connected to PF3 on the Launchpad
	SW1 left switch is negative logic PF4 on the Launchpad
*/

#include "..\..\TM4C_Common\tm4c123gh6pm.h"

#define second	1454480	//	1 second = 1454480
#define DARK	0x00	//	DARK for LEDs connected to PortF
#define RED		0x02	//	RED for LEDs connected to PortF
#define BLUE	0x04	//	BLUE for LEDs connected to PortF
#define PINK	0x06	//	PINK for LEDs connected to PortF
#define GREEN	0x08	//	GREEN for LEDs connected to PortF
#define YELLOW	0x0A	//	YELLOW for LEDs connected to PortF
#define SKYBLUE	0x0C	//	SKYBLUE for LEDs connected to PortF
#define WHITE	0x0E	//	WHITE for LEDs connected to PortF

/*	Function for Initializing Port F	*/
void PortF_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;		//	1) activate clock for Port F
	delay = SYSCTL_RCGC2_R;				//	allow time for clock to start
	GPIO_PORTF_LOCK_R = 0x4C4F434B;		//	2) unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x1F;				//	allow changes to PF4-0
	//	only PF0 needs to be unlocked, other bits can't be locked
	GPIO_PORTF_AMSEL_R = 0x00;			//	3) disable analog on PF
	GPIO_PORTF_PCTL_R = 0x00000000;		//	4) PCTL GPIO on PF4-0
	GPIO_PORTF_DIR_R = 0x0E;			//	5) PF4,PF0 in, PF3-1 out
	GPIO_PORTF_AFSEL_R = 0x00;			//	6) disable alt funct on PF7-0
	GPIO_PORTF_PUR_R = 0x11;			//	enable pull-up on PF0 and PF4
	GPIO_PORTF_DEN_R = 0x1F;			//	7) enable digital I/O on PF4-0
}

/*	Function for Initializing Port D	*/
void PortD_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000008;		//	1) activate clock for Port D
	delay = SYSCTL_RCGC2_R;				//	allow time for clock to start
	GPIO_PORTD_AMSEL_R &= ~0x00;		//	3) disable analog on PD
	GPIO_PORTD_PCTL_R = 0x00000000;		//	4) PCTL GPIO on PD
	GPIO_PORTD_DIR_R |= 0x09;			//	5) PD0, PD3 as output
	GPIO_PORTD_AFSEL_R &= ~0x09;		//	6) disable alt funct on PD0, PD3
	GPIO_PORTD_DEN_R = 0x09;			//	7) enable digital I/O on PD0, PD3
}

/*	main function	*/
int main(void)
{
	PortF_Init();	//	Port F Initialziation
	PortD_Init();	//	Port D Initialziation

	/*	Controling PD0 with SW1 & PD3 with SW2	*/
	while(1)
	{
		if((GPIO_PORTF_DATA_R &= 0x10) == 0x00)	//	if SW1 is Pressed
		{
			GPIO_PORTD_DATA_R |= 0x01;	//	PD0 to be turned ON
			GPIO_PORTF_DATA_R |= RED;	//	Checking Switch 1 with RED color LED
		}
		if((GPIO_PORTF_DATA_R &= 0x01) == 0x00)	//	if SW2 is Pressed
		{
			GPIO_PORTD_DATA_R |= 0x08;	//	PD3 to be turned ON
			GPIO_PORTF_DATA_R |= GREEN;	//	Checking Switch 2 with GREEN color LED
		}
	}
}
