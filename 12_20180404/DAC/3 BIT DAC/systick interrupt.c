#include "PLL.h"
#include "tm4c123gh6pm.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void PortA_Init(void);        // start sound output
void SysInit(void); 				//initialize SysTick timer
void SysLoad(unsigned long period); //Load reload value


//############################################################################
unsigned char Index; 
// 3-bit 16-element sine wave
const unsigned char SineWave[16] = {4,5,6,7,7,7,6,5,4,3,2,1,1,1,2,3};

// **************DAC_Init*********************
// Initialize 3-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){unsigned long volatile delay;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
  delay = SYSCTL_RCGC2_R;    // allow time to finish activating
  GPIO_PORTB_AMSEL_R &= ~0x07;      // no analog 
  GPIO_PORTB_PCTL_R &= ~0x00000FFF; // regular function
  GPIO_PORTB_DIR_R |= 0x07;      // make PB2-0 out
  GPIO_PORTB_AFSEL_R &= ~0x07;   // disable alt funct on PB2-0
  GPIO_PORTB_DEN_R |= 0x07;      // enable digital I/O on PB2-0
	GPIO_PORTB_DR8R_R|=0x07;
}

// **************DAC_Out*********************
// output to DAC
// Input: 3-bit data, 0 to 7 
// Output: none
void DAC_Out(unsigned long data){
  GPIO_PORTB_DATA_R = data;
}
//#################################################################################
int main(void){
  PLL_Init();   
	SysInit();
	SysLoad(10000);
	DAC_Init();          // Port B is DAC	
	while(1){
	}
}
void SysLoad(unsigned long period){
	NVIC_ST_RELOAD_R = period -1;
	
  Index = 0;
}

void SysInit(void){    
	NVIC_ST_CTRL_R = 0;   
  NVIC_ST_CURRENT_R = 0;        // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1               
  NVIC_ST_CTRL_R = 0x00000007;  // enable with core clock and interrupts
	
} 
// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	DAC_Out(SineWave[Index]);
  Index = (Index+1) & 0x0F;  
}
