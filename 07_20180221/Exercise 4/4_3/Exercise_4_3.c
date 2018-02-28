/*
	Exercise 4.3 : Write a C program to control speed and direction of DC motor by setting different duty cycles.
					 Use internal LEDs (green for CW, red for CCW) to indicate directions.
					T = 20 ms = 80000*20 = 1600000

		Using PortA5 for input of DC motor i.e. output from Tiva Board.
		L293D motor driver
		SW1 left switch is negative logic PF4 on the Launchpad (Using for Anti-Clockwise) --> PA5
		SW2 right switch is negative logic PF0 on the Launchpad (Using for Clockwise) --> PA6
*/

// Color    LED(s) PortF
// RED      R--    0x02
// GREEN    -G-    0x08

#include "..\..\..\TM4C_Common\tm4c123gh6pm.h"
#include "..\..\..\TM4C_Common\PLL.h"

#define TimePeriod	1600000   //20ms

unsigned long PERC50 = 0.5 * TimePeriod;
unsigned long PERC95 = 0.95 * TimePeriod;
int i;

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

/*function definition for loading Systick Reload Value and Creating a delay*/
void SysLoad(unsigned long period)
{
	NVIC_ST_RELOAD_R = period -1;			// assign the Reload register value as (Period-1), since the value in register as 0 will also incur a comparison
	NVIC_ST_CURRENT_R = 0;					// any value written to CURRENT clears 
	while((NVIC_ST_CTRL_R&0x00010000)==0);	// wait for count flag
}

/*function definition for Systick Initialization*/
void SysInit(void)
{
	NVIC_ST_CTRL_R = 0;								// Control mode register as 0
	NVIC_ST_CURRENT_R = 0;							// any write to current clears it
	NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R & 0x00FFFFFF;	// priority 0
	NVIC_ST_CTRL_R = 0x00000005;					// enable with core clock and interrupts
}

int control;

/*main function*/
int main(void)
{
	PortF_Init(); //Port F Initialziation
	PortA_Init(); //Port A Initialziation
	PLL_Init();
	SysInit();

	/*Controling PA5 with SW1 & PA6 with SW2*/
	while(1)
	{
		if((GPIO_PORTF_DATA_R & 0x11) == 0x01) //if SW1 is Pressed
		{
			control = 0x20; //PA5 to be turned ON
			for (i = PERC50; i <= PERC95; i += 100000)
			{
				GPIO_PORTF_DATA_R = 0x02;
				if((GPIO_PORTF_DATA_R & 0x11)  == 0x10) //if SW2 is Pressed
				{
					GPIO_PORTF_DATA_R = 0x08;
					GPIO_PORTA_DATA_R = 0x40;
					break;
				}
				GPIO_PORTA_DATA_R = control; //PA5 to be turned ON
				SysLoad(i);
				GPIO_PORTA_DATA_R = 0x00; //PA5 to be turned OFF
				SysLoad(TimePeriod - i);
			}
		}

		if((GPIO_PORTF_DATA_R & 0x11)  == 0x10) //if SW2 is Pressed
		{
			control = 0x40; //PA6 to be turned ON
			for (i = PERC50; i <= PERC95; i += 100000)
			{
				GPIO_PORTF_DATA_R = 0x08;
				if((GPIO_PORTF_DATA_R & 0x11) == 0x01) //if SW1 is Pressed
				{
					GPIO_PORTF_DATA_R = 0x02;
					GPIO_PORTA_DATA_R = 0x20;
					break;
				}
				GPIO_PORTA_DATA_R = control; //PA5 to be turned ON
				SysLoad(i);
				GPIO_PORTA_DATA_R = 0x00; //PA5 to be turned OFF
				SysLoad(TimePeriod - i);
			}
		}

		GPIO_PORTA_DATA_R = control; //PA5/6 based on last input to be turned ON
	}
}
