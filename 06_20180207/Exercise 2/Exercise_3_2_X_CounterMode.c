/*
	Exercise 3.2.i : Using Systick timer, provide a delay of 0.2s to blink the LED.
						(i) Using counter method
	Approach: Using Loop due to the below reason
	Note: Max Value that Reload Register can store for SysTick is 8388607 i.e. 2^23 - 1
			Larger values may work ONCE in the logic analyser but not on board for sure
			So to do 0.2s we might be using another loop.
*/

#include "..\..\TM4C_Common\tm4c123gh6pm.h"
#include "..\..\TM4C_Common\PLL.h"

#define BLUE	0x0F	//BLUE for LEDs connected to PortF
#define basic_delay_period	40000	//ticks for 500us

unsigned long up_lim = 2000;		//upper limit to for looping delay
unsigned long lo_lim = 100;			//lower limit to for looping delay
unsigned int loop_lim;				//loop limit for current looping delay
int loop_gradient = 200;			//increment factor for every looping delay
int sign = -1;						//increment or decrement!!
int pulse_length = 2;				//number of pulses for each time period
int i, j;							//loop variable

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
	loop_lim = 400;

	while(1)
	{
		for(i = 0; i < 2*pulse_length; i++)
		{
			GPIO_PORTF_DATA_R ^= BLUE; //Blink LED with color BLUE
			for(j = 0; j < loop_lim; j++)
				SysLoad(basic_delay_period);
		}
		loop_lim = loop_lim + (sign*loop_gradient);
		if(loop_lim >= up_lim)
			sign = -1;
		else
			if(loop_lim <= lo_lim)
				sign = 1;
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
