
#include "PLL.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "PLL.h"
#include "UART.h"
#include "string.h"
void PortF_Init();

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}

void PortD_Init(void)
{
	unsigned long volatile delay;
	/*PORT Initialization*/
	SYSCTL_RCGC2_R |= 0x08; // Port d clock
	delay = SYSCTL_RCGC2_R; // wait 3-5 bus cycles
	GPIO_PORTD_DIR_R |= 0x07; // PA5 output
	GPIO_PORTD_AFSEL_R &= ~0x07; // not alternative
	GPIO_PORTD_AMSEL_R &= ~0x07; // no analog
	GPIO_PORTD_PCTL_R &= ~0x00000FFF; // bits for PA5
	GPIO_PORTD_DEN_R |= 0x07; // enable PA5
}
// delay function for testing from sysctl.c
// which delays 3*ulCount cycles

void Delay(unsigned long ulCount){
  do{
    ulCount--;
	}while(ulCount);
}


void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}



int main(void){
	//unsigned char i;
  char string[20];  // global to assist in debugging

  PLL_Init(); 
	UART_Init();              // initialize UART
  OutCRLF();	// set system clock to 50 MHz
 
	
  


	PortF_Init();
  PortD_Init();         
  while(1){
		UART_OutString("Enter Number: ");
    UART_InString(string,19);
   if( strcmp(string,"0")== 0){
				GPIO_PORTD_DATA_R = (0x01);
				UART_OutString(" PD0 LED glowing ");}
	 else if(strcmp(string,"1")== 0){
				GPIO_PORTD_DATA_R = (0x02);
				UART_OutString(" PD1 ");}
	 else if(strcmp(string,"2")== 0){
				GPIO_PORTD_DATA_R = (0x04);
				UART_OutString(" PD2 ");}
	
  }
           
  
}

