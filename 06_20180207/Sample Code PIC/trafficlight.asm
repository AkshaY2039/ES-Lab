CounterA 	equ 022h
CounterB 	equ 023h
CounterC 	equ 024h
Red		equ B'00000001'
Amber		equ B'00000010'
Green		equ B'00000100'
REDLIFE		equ 30
GREENLIFE	equ 30
AMBLIFE		equ 02


  org   0X00 
 	goto Mainloop
Init
  bsf	STATUS, RP0	; Prepare to access bank1
  clrf	TRISB		; TRISB Setup all bits of 												; PORTB as outputs
  bcf	STATUS, RP0   	
  return

Mainloop
  call  Init
  movlw	Red		; Excite RED
  movwf	PORTB		; PORTB with 1
  movlw REDLIFE		; Hold RED for REDLIFE
  movwf CounterA
  call	Delay		; Create Delay
  movlw	Amber		; Turn off RED,Excite Amber 
  movwf	PORTB		; PORTB with 1
  movlw AMBLIFE		; Hold Amber for short time
  movwf CounterA
  call	Delay		; Create Delay
  movlw	Green		; Turn off Yellow,Excite Green 
  movwf	PORTB		; PORTB with 1
  movlw GREENLIFE	; Hold Green for GREENLIFE
  movwf CounterA
  call	Delay		; Create Delay
  goto	Mainloop	; Repeat Mainloop
  
 
Delay 
  movlw D'1'
  movwf CounterC
  movlw D'1'
  movwf CounterB

loop
  decfsz CounterA,1
  goto loop
  decfsz CounterB,1
  goto loop
  decfsz CounterC,1
  goto loop
  return
