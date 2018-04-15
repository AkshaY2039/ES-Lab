/*
Resolution : Voltage / total number of combinations
Default:
	0.7ms for -90 degree
	1.5ms for 0 degree
	2.3ms for +90 degree
*/

#include "..\..\TM4C_Common\tm4c123gh6pm.h"
#include "..\..\TM4C_Common\PLL.h"

#define pulse_width 1600000 //20 ms
/*#define Degree_90	56000	//-90 degree
#define Degree0		130000	//0 degree
#define Degree90	208000	//90 degree*/
#define Degree_90	0.3*80000	//-90 degree
#define Degree0		1.0*80000	//0 degree
#define Degree90	2.0*80000	//90 degree
#define delta		2000

/*Function Prototypes here or say function Declarations*/
void PortD_Init(void);				// function for Initialization of Port D for sound Outputs
void SysInit(void);					// initialize SysTick timer
void SysLoad(unsigned long period);	// Load reload value to SysTick timer
unsigned long on_duty;
int i;

/*main function*/
int main(void)
{
	PLL_Init();
	PortD_Init();
	SysInit();

	on_duty = Degree0;
	
	//0 to 90 degree
	do
	{
		for(i = 0; i < 5; i++)
		{
			GPIO_PORTD_DATA_R=0x01;
			SysLoad(on_duty);
			GPIO_PORTD_DATA_R=0x00;
			SysLoad(pulse_width - on_duty);
		}
		if(on_duty >= Degree90)
			break;
		else
			on_duty += delta;
	}while(1);

	//gap of 1 s
	for(i = 0; i < 50; i++)
	{
		SysLoad(pulse_width);
	}

	//90 to 0 degree
	do
	{
		for(i = 0; i < 5; i++)
		{
			GPIO_PORTD_DATA_R=0x01;
			SysLoad(on_duty);
			GPIO_PORTD_DATA_R=0x00;
			SysLoad(pulse_width - on_duty);
		}
		if(on_duty <= Degree0)
			break;
		else
			on_duty -= delta;
	}while(1);

	//gap of 1 s
	for(i = 0; i < 50; i++)
	{
		SysLoad(pulse_width);
	}

	//0 to -90 degree
	do
	{
		for(i = 0; i < 5; i++)
		{
			GPIO_PORTD_DATA_R=0x01;
			SysLoad(on_duty);
			GPIO_PORTD_DATA_R=0x00;
			SysLoad(pulse_width - on_duty);
		}
		if(on_duty <= Degree_90)
			break;
		else
			on_duty -= delta;
	}while(1);
}

/*function definition for Port D Initialization*/
void PortD_Init(void)
{
	unsigned long volatile delay;
	/*PORT Initialization*/
	SYSCTL_RCGC2_R |= 0x08;				// Port D clock
	delay = SYSCTL_RCGC2_R;				// wait 3-5 bus cycles
	GPIO_PORTD_DIR_R |= 0x01;			// PD0 output
	GPIO_PORTD_AFSEL_R &= ~0x01;		// not alternative
	GPIO_PORTD_AMSEL_R &= ~0x01;		// no analog
	GPIO_PORTD_PCTL_R &= ~0x00F00000;	// bits for PD0
	GPIO_PORTD_DEN_R |= 0x01;			// enable PD0
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
