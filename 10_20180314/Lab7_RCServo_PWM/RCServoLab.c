// 0.Documentation Section 
// SoftSound.c
// Runs on LM4F120 or TM4C123
// Use the SysTick timer to request interrupts at 500Hz.
// Jonathan Valvano
// November 3, 2013


#include "PLL.h"
#include "tm4c123gh6pm.h"
// Constant declarations to access port registers using 
// symbolic names instead of addresses
unsigned long ADC0_InSeq3(void);
void ADC0_InitSWTriggerSeq3_Ch1(void);
void SysTick_Wait10ms(unsigned long delay);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void Port_Init(void);        // start sound output
void SysFun(void);
void SysLoad(unsigned long period);
unsigned int i=0;
unsigned int pwidth=56000;
//unsigned int nwidth =184000;
unsigned int ADCvalue;
	//unsigned int i=0;
	
// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){
  PLL_Init();   
	
	SysFun();
  	// 80 MHz
	ADC0_InitSWTriggerSeq3_Ch1(); 
  Port_Init();   
	// initialize output and interrupts
  EnableInterrupts();
	/*Initialize ports and timers*/
  while(1){   
		/*Your code goes here*/
		 
	
	
  }
}
// **************Port_Init*********************
// Initialize SysTick periodic interrupts
// Input: none
// Output: none
void Port_Init(void){ unsigned long volatile delay;
  SYSCTL_RCGC2_R |= 0x00000001; // activate port A
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTA_AMSEL_R &= ~0x20;      // no analog 
  GPIO_PORTA_PCTL_R &= ~0x00F00000; // regular function
  GPIO_PORTA_DIR_R |= 0x20;     // make PA5 out
  GPIO_PORTA_DR8R_R |= 0x20;    // can drive up to 8mA out
  GPIO_PORTA_AFSEL_R &= ~0x20;  // disable alt funct on PA5
  GPIO_PORTA_DEN_R |= 0x20;     // enable digital I/O on PA5
}

void SysLoad(unsigned long period){

	
	NVIC_ST_RELOAD_R = period-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
	
}

void SysFun(void){
	
	NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;
          
} 

void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<=delay; i++){
    SysLoad(800000);  // wait 10ms
  }
}


void ADC0_InitSWTriggerSeq3_Ch1(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;   // 1) activate clock for Port E
  delay = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize
  GPIO_PORTE_DIR_R &= ~0x04;      // 2) make PE2 input
  GPIO_PORTE_AFSEL_R |= 0x04;     // 3) enable alternate function on PE2
  GPIO_PORTE_DEN_R &= ~0x04;      // 4) disable digital I/O on PE2
  GPIO_PORTE_AMSEL_R |= 0x04;     // 5) enable analog function on PE2
  SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0 
  delay = SYSCTL_RCGC2_R;         
  SYSCTL_RCGC0_R &= ~0x00000300;  // 7) configure for 125K 
  ADC0_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
  ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1; // 11) channel Ain1 (PE2)
  ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC0_ACTSS_R |= 0x0008;         // 13) enable sample sequencer 3
}






//------------ADC0_InSeq3------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC0_InSeq3(void){  
	unsigned long result;
  ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
  return result;
}




