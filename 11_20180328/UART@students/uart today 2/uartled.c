
#include "PLL.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "PLL.h"
#include "UART.h"
#include "string.h"

#define black     0x00
#define red       0x02
#define blue      0x04
#define green     0x08
#define yellow    0x0A
#define sky_blue  0x0C
#define white     0x0E
#define pink      0x06

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
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000008;   // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;       // allow time for clock to start
  GPIO_PORTD_AMSEL_R = 0x00;    // 3) disable analog on PD
  GPIO_PORTD_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PD
  GPIO_PORTD_DIR_R = 0x00;     // 5) PD0 - PD2 as output
  GPIO_PORTD_AFSEL_R = 0x00;    // 6) disable alt funct
  GPIO_PORTD_DEN_R = 0x01;      // 7) enable digital I/O
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
  OutCRLF();  // set system clock to 50 MHz
 

  PortF_Init();
  PortD_Init();
           
  while(1){
    if((GPIO_PORTD_DATA_R & 0x01) == 0x01)
    {
      UART_OutString("   ENDED Session ");
      break;
    }
    UART_OutString("   Enter colour: ");
    UART_InString(string,19);
   if( strcmp(string,"black")== 0)
   {
        GPIO_PORTF_DATA_R = black;
        UART_OutString("   No LED glowing...");
      }
   if( strcmp(string,"red")== 0)
   {
        GPIO_PORTF_DATA_R = red;
        UART_OutString("   red LED glowing...");
      }
   if( strcmp(string,"blue")== 0)
   {
        GPIO_PORTF_DATA_R = blue;
        UART_OutString("   blue LED glowing...");
      }
   if( strcmp(string,"green")== 0)
   {
        GPIO_PORTF_DATA_R = green;
        UART_OutString("   green LED glowing...");
      }
   if( strcmp(string,"yellow")== 0)
   {
        GPIO_PORTF_DATA_R = yellow;
        UART_OutString("   yellow LED glowing...");
      }
   if( strcmp(string,"sky_blue")== 0)
   {
        GPIO_PORTF_DATA_R = sky_blue;
        UART_OutString("   sky_blue LED glowing...");
      }
   if( strcmp(string,"pink")== 0)
   {
        GPIO_PORTF_DATA_R = pink;
        UART_OutString("   pink LED glowing...");
      }
   if( strcmp(string,"white")== 0)
   {
        GPIO_PORTF_DATA_R = white;
        UART_OutString("   white LED glowing...");
      }
  }        
  
}
