// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "tm4c123gh6pm.h"
//unsigned long data1[5000];
unsigned long i=0;

unsigned char Index;

/*const unsigned char SineWave[64]={32,35,38,41,44,47,49,52,54,56,58,				
  59,61,62,62,63,63,63,62,62,61,59,				
  58,56,54,52,49,47,44,41,38,35,				
  32,29,26,23,20,17,15,12,10,8,				
  6,5,3,2,2,1,1,1,2,2,3,				
  5,6,8,10,12,15,17,20,23,26,29};*/

//const unsigned char SineWave[64]={32, 35, 38, 41, 44, 47, 50, 52, 55, 57, 58, 59, 60, 61, 62, 63, 63, 63, 62, 61, 60, 59, 58, 57, 55, 52, 50, 47, 44, 41, 38, 35, 32, 29, 26, 23, 20, 17, 14, 12, 9, 7, 5, 4, 2, 1, 1, 0, 0, 0, 1, 1, 2, 4, 5, 7, 9, 12, 14, 17, 20, 23, 26, 29 };
const unsigned char SineWave[16] = {8, 11, 13, 14, 15, 14, 13, 11, 8, 5, 2, 1, 0, 1, 2, 5 };
//const unsigned char SineWave[101]={ 15, 15, 15, 15, 14, 14, 14, 14, 14, 14,
//																		 14, 13, 13, 13, 13, 13, 13, 13, 13, 12,
//																		 12, 12, 12, 12, 12, 12, 12, 11, 11, 11,
//																			11, 11, 11, 11, 11, 11, 10, 10, 10, 10,
//																		10, 10, 10, 10, 10, 10, 9, 9, 9, 9,
//																		9, 9, 9, 9, 9, 9, 9, 8, 8, 8,
//																		8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
//																			7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
//																		7, 7, 7, 7, 6, 6, 6, 6, 6, 6,
//																		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};

	




// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	Index=0;
	DAC_Init();
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1      
  NVIC_ST_CTRL_R = 0x07;  // enable SysTick with core clock and interrupts
	
  
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
	//Index = 0;
           // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	DAC_Out(0x00);
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	//GPIO_PORTF_DATA_R ^= 0x08; 
//if(Index<64){	// toggle PF3, debugging
  
  DAC_Out(SineWave[Index]);
	Index = (Index+1)&0x0F;
//}
//else{
//	Index=0;}
//	if(i<5000){
//		data1[i]=Index;
//	 i++;}
   
}
