WT		equ 020h
STATUST 	equ 021h
CounterA 	equ 022h
CounterB 	equ 023h
CounterC 	equ 024h
Green1		equ B'00000001'
Green8		equ B'10000000'


  org   0X00 
 	goto Mainloop
  org   0X04 
 	goto T2TimerHandle
Init
  movlw	B'10000001'	; Excite bit 1 of PORTB
  movwf	PORTB		; PORTB with 1
  bsf	STATUS, RP0	; Prepare to access bank1
  clrf	TRISB		; TRISB Setup all bits of 												; PORTB as outputs
  bcf	STATUS, RP0   	
  movlw B'01111010'	; pre 16, post 10
  movwf T2CON		; H12 move it to T2CON
  movlw B'11111001' 	; load 249 to
  bsf  STATUS, RP0	; PR2 is in bank 1
  movlw PR2		; move 249 to PR2
  bsf PIE1, TMR2IE	; enable Timer 2 interrupt
  bcf STATUS, RP0	; back to bank 0 
  bsf PIR1, TMR2IF	; enable timer to signal
  bsf INTCON, GIE	; enable Generic interrupt
  bcf INTCON, PEIE	; disable peripheral interrupt
  return

Mainloop
  call  Init
  call	Delay		; Blink LED
  call	Blink 		; Insert delay
  bsf 	T2CON, 2	; start the Timer 2
  bsf   INTCON, PEIE	; enable peripheral interrupt
  goto	Mainloop	; Repeat Mainloop
  
T2TimerHandle
  bcf INTCON, GIE	; disable peripheral interrupt  
  movwf	WT		; working register content in W_T
  swapf	STATUS, W	; STATUS reg swapped into W
  movwf STATUST		; move the content to STATUS_T
 
  movlw	Green1		;
  xorwf PORTB,F		; Toggle green LED
  bcf 	T2CON, 2	; stop the Timer 2
  bcf   INTCON, PEIE	; Disable peripheral interrupt		  

  swapf	STATUST,W	; STATUS_T swapped into W
  movwf	STATUS		; moved to STATUS register
  swapf	WT, F		; swap the content of W_T
  swapf	WT, W		; swap W_T into W
  retfie	   	; enable interrupts and return to main

Delay 
  movlw D'1'
  movwf CounterC
  movlw D'1'
  movwf CounterB
  movlw D'5'
  movwf CounterA
loop
  decfsz CounterA,1
  goto loop
  decfsz CounterB,1
  goto loop
  decfsz CounterC,1
  goto loop
  return

Blink	

  movlw		Green8		;
  xorwf   	PORTB,F		; Toggle green LED		 
  return 