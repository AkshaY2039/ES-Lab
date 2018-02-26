/*
	Exercise 4.2 : Interface a DC motor and control the motor speed using PWM pulse generated using Systick timer. 
					Duty cycle should vary from 50% to 95%.
					T = 20 ms = 80000*20 = 1600000

		Using PortA5 for input of DC motor i.e. output from Tiva Board.
		L293D motor driver
*/

#include "..\..\..\TM4C_Common\tm4c123gh6pm.h"
#include "..\..\..\TM4C_Common\PLL.h"

#define TimePeriod	1600000   //20ms

unsigned long PERC50 = 0.5 * TimePeriod;
unsigned long PERC95 = 0.95 * TimePeriod;
int i;

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

/*main function*/
int main(void)
{
	PortA_Init(); //Port A Initialziation
	PLL_Init();
	SysInit();

	for (i = PERC50; i <= PERC95; i += 100000)
	{
		GPIO_PORTA_DATA_R = 0x20; //PA5 to be turned ON
		SysLoad(i);
		GPIO_PORTA_DATA_R = 0x00; //PA5 to be turned OFF
		SysLoad(TimePeriod - i);
	}

	while(1)
	{
		GPIO_PORTA_DATA_R = 0x20; //PA5 to be turned ON
		SysLoad(PERC95);
		GPIO_PORTA_DATA_R = 0x00; //PA5 to be turned OFF
		SysLoad(TimePeriod - PERC95);
	}
}
