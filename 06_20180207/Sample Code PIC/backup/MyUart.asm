; uart - both transmit And receive
; make sure the stop Bit is initialized To 0



	org 0x00
init:
	clrf PORTC
	; prepare To work with h / W uart interface
	movlw b'00010000' ;SET PB4 AS INPUT AND THE REST PORTB AS OUTPUT
	movwf TRISB
	movlw b'00000111' ;DISABLE COMPARATORS MODULES
	movwf CMCON
	bcf OPTION_REG, 7 ;Enable pull - up resistors of PORTB
	; ready To use h / W uart interface
	
	bsf   STATUS, RP0
	movlw b'11000000'  ;SET PC7 and PC8 as INPUTs using TRISC
	movwf TRISC
	
	movlw D'25'
	movwf SPBRG ;Save 25 To SPBRG For 9600 baud rate
	
	movlw b'00100110' ;Setup TXSTA for UART TX
	movwf TXSTA ;
	bsf TXSTA, TRMT
	
	bcf   STATUS, RP0

	movlw b'10110000'
	movwf RCSTA ;setup RCSTA For uart RC

	
mainloop
	btfsc PORTB, 4 ; enter a value in h / W uart simulator To test RC
	Goto mainloop
	
rctxloop
	btfss PIR1, RCIF ; check If the Input is ready in RCREG
	Goto rctxloop
	movf RCREG, W
	movwf TXREG

txloop	
	btfsc PIR1, TXIF
	Goto txloop
	Goto rctxloop

End Goto End ; superfluous                        

	