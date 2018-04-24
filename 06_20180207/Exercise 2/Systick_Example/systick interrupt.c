// 0.Documentation Section 
// 
// Runs on LM4F120 or TM4C123
// Use the SysTick timer to request interrupts .
// Jonathan Valvano
// November 3, 2013


#include "PLL.h"
#include "tm4c123gh6pm.h"

#define sec2 40000

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void PortA_Init(void);        // start sound output
void SysInit(void); 				//initialize SysTick timer
void SysLoad(unsigned long period); //Load reload value
void PortF_Init(void); //Port F Init
int variable_time = 100*sec2;

int main(void){
  PLL_Init();   
	PortA_Init();
	PortF_Init(); //Port F Initialziation
	SysInit();
  //SysLoad(40000/*  reload value*/); 
	SysLoad(variable_time); //for Exercise2

	while(1){
	}
	// initialize output and interrupts
  // EnableInterrupts();
  /*Initialize necessary ports and timers here*/
	
	 
  
}
// **************Sound_Init*********************
// Initialize SysTick periodic interrupts
// Input: none
// Output: none
void PortA_Init(void){ unsigned long volatile delay;
  /*PORT Initialization*/
	SYSCTL_RCGC2_R |= 0x01;           // Port A clock
  delay = SYSCTL_RCGC2_R;              // wait 3-5 bus cycles
  GPIO_PORTA_DIR_R |= 0x40;           // PA6 output
  GPIO_PORTA_AFSEL_R &= ~0x40;      // not alternative
  GPIO_PORTA_AMSEL_R &= ~0x40;      // no analog
  GPIO_PORTA_PCTL_R &= ~0x0F000000; // bits for PA6
  GPIO_PORTA_DEN_R |= 0x40;         

}

void SysLoad(unsigned long period){
	NVIC_ST_RELOAD_R = period -1;
	
}

void SysInit(void){
           
	NVIC_ST_CTRL_R = 0;   
  NVIC_ST_CURRENT_R = 0;        // any write to current clears it
  NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF; // priority 0                
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts
	
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

// Interrupt service routine
// 
void SysTick_Handler(void){
	
/*Your code goes here*/
	GPIO_PORTA_DATA_R ^= 0x40;
	GPIO_PORTF_DATA_R ^= 0x08;
	if(variable_time <= sec2)
	{
		variable_time = 100*sec2;
	}
	else
	{
		variable_time -= 10000;
	}		
}
