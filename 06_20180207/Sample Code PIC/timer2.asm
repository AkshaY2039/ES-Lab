Green		equ B'00000001'
WT		equ 020h
STATUST 	equ 021h

  org   0X00 
 	goto Mainloop
  org   0X04 
 	goto T2TimerHandle

Mainloop
  Call Initial
  Call T2FourMs
  bsf  T2CON, 2		; Enable the Timer 2
  bsf  INTCON, PEIE	; Enable peripheral interrupt
  goto Mainloop		; Repeat Mainloop

Initial
  movlw	Green		; Excite bit 1 of PORTB
  movwf	PORTB		; PORTB with 1
  bsf	STATUS, RP0	; Prepare to access bank1
  clrf	TRISB		; TRISB Setup all bits of 												; PORTB as outputs
  bcf	STATUS, RP0   
  return

T2FourMs	
  movlw B'01001010'	; pre 16, post 10
  movwf T2CON		; H12 move it to T2CON
  movlw B'11111001' 	; load 249 to
  bsf  STATUS, RP0	; PR2 is in bank 1
  movlw PR2		; move 249 to PR2
  bsf PIE1, TMR2IE	; enable Timer 2 interrupt
  bcf STATUS, RP0	; back to bank 0 
  bsf PIR1, TMR2IF	; enable timer to signal
  bsf INTCON, GIE	; enable Generic interrupt
  bcf INTCON, PEIE	; Disable peripheral interrupt
 			; Note; Timer2 is still disabled
  return		; return and wait for Timer2 interrupt

T2TimerHandle
  bcf INTCON, GIE	; disable peripheral interrupt  
  movwf	WT		; working register content in W_T
  swapf	STATUS, W	; STATUS reg swapped into W
  movwf STATUST		; move the content to STATUS_T
 
  movlw	Green		;
  xorwf PORTB,F		; Toggle green LED
  bcf T2CON, 2		; Disable the Timer 2
  bcf INTCON, PEIE	; Disable peripheral interrupt		  

  swapf	STATUST,W	; STATUS_T swapped into W
  movwf	STATUS		; moved to STATUS register
  swapf	WT, F		; swap the content of W_T
  swapf	WT, W		; swap W_T into W
  retfie	   	; enable interrupts and return to main


