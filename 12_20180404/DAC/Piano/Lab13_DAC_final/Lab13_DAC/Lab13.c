// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 5-0 have the 6-bit DAC
// Port E bits 3-0 have 4 piano keys

/*
  SW1 - 261 Hz
  SW2 - 440 Hz
  SW3 - 550 Hz
  SW4 - 987 Hz
*/

#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

const unsigned int FreqSw[4] = {261, 440, 550, 987};

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);
int main(void){ // Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
// PortE used for piano keys, PortB used for DAC        
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
	DisableInterrupts();
  
    // enable after all initialization are done
  while(1){                
// input from keys to select tone
	//	Sound_Tone(2390);
	if((Piano_In()&0x01)==0x01)
  {			
      EnableInterrupts();
			Sound_Tone(80000000/(FreqSw[0]*16));
      //Sound_Tone(6378);
			//Sound_Tone(2390);
//			//Sound_Tone(1000 );
		}
		else if((Piano_In()&0x02)==0x02)
      {
      EnableInterrupts();
      Sound_Tone(80000000/(FreqSw[1]*16));
//			//Sound_Tone(7584);
//			Sound_Tone(2129);
		}
		else if((Piano_In()&0x04)==0x04){
//			
			EnableInterrupts();
      Sound_Tone(80000000/(FreqSw[2]*16));
//			Sound_Tone(1896);
//			//Sound_Tone(1341);
		}
		else if((Piano_In()&0x08)==0x08){
//			
			EnableInterrupts();
      Sound_Tone(80000000/(FreqSw[3]*16));
//			Sound_Tone(1596);
//			//Sound_Tone(4780);
		}
		else{
			Sound_Off();
		DisableInterrupts();
  }
		delay(10);
//			

}
//	
            
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}


