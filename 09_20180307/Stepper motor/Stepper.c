// steo angle came to be 1.8 degrees

#include "..\..\TM4C_Common\tm4c123gh6pm.h"
#include "..\..\TM4C_Common\PLL.h"

#define delay_period 10000

/*Function Prototypes here or say function Declarations*/
void PortD_Init(void);				// function for Initialization of Port D for sound Outputs
void SysInit(void);					// initialize SysTick timer
void SysLoad(unsigned long period);	// Load reload value to SysTick timer
int i,j;

/*main function*/
int main(void)
{
	PLL_Init();
	PortD_Init();
	SysInit();

	for(i=0; i < 25; i++)
	{
		GPIO_PORTD_DATA_R = 0x05;
		for(j=0; j < 100; j++)
			SysLoad(delay_period);
		GPIO_PORTD_DATA_R = 0x06;
		for(j=0; j < 100; j++)
			SysLoad(delay_period);
		GPIO_PORTD_DATA_R = 0x0A;
		for(j=0; j < 100; j++)
			SysLoad(delay_period);
		GPIO_PORTD_DATA_R = 0x09;
		for(j=0; j < 100; j++)
			SysLoad(delay_period);
	}
}

/*function definition for Port A Initialization*/
void PortD_Init(void)
{
	unsigned long volatile delay;
	/*PORT Initialization*/
	SYSCTL_RCGC2_R |= 0x08;				// Port D clock
	delay = SYSCTL_RCGC2_R;				// wait 3-5 bus cycles
	GPIO_PORTD_DIR_R |= 0x0F;			// PD5 output
	GPIO_PORTD_AFSEL_R &= ~0x0F;		// not alternative
	GPIO_PORTD_AMSEL_R &= ~0x0F;		// no analog
	GPIO_PORTD_PCTL_R &= ~0x00F00000;	// bits for PD5
	GPIO_PORTD_DEN_R |= 0x0F;			// enable PD5
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
