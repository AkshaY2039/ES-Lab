; READ this comment before you get started.
;
; If this is your first program, do the following
; launch PIC IDE from start menu
; Launch Assembler from Tools drop down menu
; Cut paste the content of this file in the Assembler screen. 
; "Assemble and Load" (Tools menu of Assemble)
;		 This loads this program in simulator 
; Launch 8xLED from PIC IDE Tools drop down menu
; Run your code with Simulation->Start at different rate.

CounterC 	equ	022h
CounterB 	equ 021h
CounterA 	equ 020h
MaxCount	equ 32
Green		equ B'00000001'
BLNKCNT		equ 023h

Mainline
	Call Initial

Mainloop	
	call	Blink		; Blink LED
	call	Delay 		; Insert delay
	goto	Mainloop	; Repeat Mainloop

Delay 
	movlw D'1'
	movwf CounterC
	movlw D'1'
	movwf CounterB
	movlw D'150'
	movwf CounterA
loop
	decfsz CounterA,1
	goto loop
	decfsz CounterB,1
	goto loop
	decfsz CounterC,1
	goto loop
	return

Initial
	movlw	MaxCount	; Initialize GPR at BLNKCNT
	movwf	BLNKCNT		; Store MaxCount in GPR 32
	movlw	Green		; Excite bit 1 of PORTB
	movwf	PORTB		; PORTB with 1
	bsf		STATUS, RP0	; Prepare to access bank1
	clrf	TRISB		; TRISB Setup all bits of 	; PORTB as outputs
	bcf		STATUS, RP0
	return

Blink	
	decfsz	BLNKCNT,F	;	
	goto	Blinkend	;	
	movlw	MaxCount	; reload	
	movwf	BLNKCNT		; with 50
	movlw	Green		;
	xorwf	PORTB, F	; Toggle green LED

BlinkEnd		 
	return