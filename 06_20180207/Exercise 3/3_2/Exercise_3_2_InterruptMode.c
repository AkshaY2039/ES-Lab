/*
	Exercise 3.2.ii : Using Systick timer, provide a delay of 0.2s to blink the LED.
						(ii) using interrupt method
	Note: Max Value that Reload Register can store for SysTick is 8388607 i.e. 2^23 - 1
			Larger values may work ONCE in the logic analyser but not on board for sure
			So to do 0.2s we might be using another loop.*/

#include "..\..\..\TM4C_Common\tm4c123gh6pm.h"
#include "..\..\..\TM4C_Common\PLL.h"

#define BLUE	0x04	//BLUE for LEDs connected to PortF

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
	SysLoad(40000); //Reload Systick Timer with the value

	while(1);
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

/*function definition for loading Systick Reload Value*/
void SysLoad(unsigned long period)
{
	NVIC_ST_RELOAD_R = period -1;
}

/*function definition for Systick Initialization*/
void SysInit(void)
{
	NVIC_ST_CTRL_R = 0;								// Control mode register as 0
	NVIC_ST_CURRENT_R = 0;							// any write to current clears it
	NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R & 0x00FFFFFF;	// priority 0
	NVIC_ST_CTRL_R = 0x00000007;					// enable with core clock and interrupts
}

/*Systick Handler Definition - Interrupt Routine*/
void SysTick_Handler(void)
{
	GPIO_PORTF_DATA_R ^= BLUE; //Blink LED with color BLUE
}
