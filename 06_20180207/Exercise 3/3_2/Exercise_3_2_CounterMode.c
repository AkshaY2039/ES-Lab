/*
	Exercise 3.2.i : Using Systick timer, provide a delay of 0.2s to blink the LED.
						(i) Using counter method
	Note: Max Value that Reload Register can store for SysTick is 8388607 i.e. 2^23 - 1
			Larger values may work ONCE in the logic analyser but not on board for sure
			So to do 0.2s we might be using another loop.
*/

#include "..\..\..\TM4C_Common\tm4c123gh6pm.h"
#include "..\..\..\TM4C_Common\PLL.h"

#define BLUE	0x04	//BLUE for LEDs connected to PortF
#define second_0_2	16000000	//ticks for 0.2s

unsigned long delay_period = second_0_2;	//delay period to be used
unsigned long time_grad = 2000000;			//ticks by which delay to be changed at a time
unsigned long up_lim = 5*second_0_2;		//upper limit to change sign with
unsigned long lo_lim = second_0_2/5;		//lower limit to change sign with
int pulse_length = 2;			//number of pulses for each time period
int i;							//loop variable

/*Function Prototypes here or say function Declarations*/
void PortF_Init(void);				// function for Initialization of Port F
void SysInit(void);					// initialize SysTick timer
void SysLoad(unsigned long period);	// Load reload value to SysTick timer

/*main function*/
int main(void)
{
	PLL_Init();
	PortF_Init();
	SysInit();

	while(1)
	{
		for(i = 0; i < 2*pulse_length; i++)
		{
			GPIO_PORTF_DATA_R ^= BLUE; //Blink LED with color BLUE
			SysLoad(delay_period); //Reload Systick Timer with the value
		}
		delay_period -= time_grad;
		if(delay_period <= lo_lim)
			delay_period = up_lim;
	}
}

/*function definition for Port F Initialization*/
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
