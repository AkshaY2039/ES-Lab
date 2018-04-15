// input signal connected to PE2/AIN1

#include "ADCSWTrigger.h"
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include <stdint.h>

#define TimePeriod	1600000   //20ms

void PortF_Init(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void SysFun(void);
void SysInit(void);//initialize SysTick timer
void SysLoad(unsigned long period);
volatile unsigned long ADCvalue;
unsigned long OnDuty;
unsigned long HalfTime = TimePeriod / 2;
int control;

int main(void){unsigned long volatile delay;
	PortF_Init();
	SysFun();
	SysInit();
  PLL_Init();                           // 80 MHz
  ADC0_InitSWTriggerSeq3_Ch1();         // ADC initialization PE2/AIN1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // activate port F
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_DIR_R |= 0x04;             // make PF2 out (built-in LED)
	GPIO_PORTA_DR8R_R |= 0x30;            // enable 8 mA drive on PA5-4
  GPIO_PORTF_AFSEL_R &= ~0x04;          // disable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;             // enable digital I/O on PF2
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF

  while(1){
  	if((GPIO_PORTF_DATA_R & 0x11) == 0x01) //if SW1 is Pressed
		control=0x08;
	if((GPIO_PORTF_DATA_R & 0x11)  == 0x10) //if SW2 is Pressed
		control=0x02;
		ADCvalue=ADC0_InSeq3();
		OnDuty = HalfTime + (0.9 * HalfTime) * ADCvalue / 4095;
		GPIO_PORTF_DATA_R=control;
		SysLoad(OnDuty);
		GPIO_PORTF_DATA_R=0x00;
		SysLoad(TimePeriod - OnDuty);
  }
}

void SysLoad(unsigned long period)
{
	NVIC_ST_RELOAD_R = period -1;
	NVIC_ST_CURRENT_R = 0;  
	
  	// any value written to CURRENT clears  
	while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag 
		}
}
void SysInit(void)
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;// any write to current clears it
	NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF;// priority 0
	NVIC_ST_CTRL_R = 0x00000005;// enable with core clock and interrupts
}
void SysFun(void)
{
	NVIC_ST_CTRL_R = 0;               // disable SysTick during setup  
	NVIC_ST_CTRL_R = 0x00000005; 
}

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
