// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

#include "PLL.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "PLL.h"
#include "UART.h"
#include "string.h"
void PortF_Init(void);

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
           
  while(1){
		UART_OutString("Enter Number: ");
    UART_InString(string,19);
   if(strcmp(string,"red")== 0){
				GPIO_PORTF_DATA_R = (0x02);
	 }
	 else if(strcmp(string,"blue")== 0){
				GPIO_PORTF_DATA_R = (0x04);
	 }
	 else if(strcmp(string,"green")== 0){
				GPIO_PORTF_DATA_R = (0x08);
	 }
	 else if(strcmp(string,"sky blue")== 0){
				GPIO_PORTF_DATA_R = (0x0C);
	 }
	 else if(strcmp(string,"white")== 0){
				GPIO_PORTF_DATA_R = (0x0E);
	 }
	 else if(strcmp(string,"pink")== 0){
				GPIO_PORTF_DATA_R = (0x06);
	 }
	 else if(strcmp(string,"yellow")== 0){
				GPIO_PORTF_DATA_R = (0x0A);
	 }
	 else{
				GPIO_PORTF_DATA_R = (0x00);
				UART_OutString(" No LED glowing ");}
  }  
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
