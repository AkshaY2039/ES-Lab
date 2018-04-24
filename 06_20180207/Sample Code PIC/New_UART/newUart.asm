; UART - both transmit and receive
; Make sure the STOP Bit is initialized to 0



	ORG 0x00
Init:
	CLRF PORTC
	; Prepare to work with H/W UART Interface
	MOVLW B'00010000' ;SET PB4 AS INPUT AND THE REST PORTB AS OUTPUT
	MOVWF TRISB	
	MOVLW B'00000111' ;DISABLE COMPARATORS MODULES
	MOVWF CMCON
	BCF OPTION_REG, 7 ;ENABLE PULL-UP RESISTORS OF PORTB
	; Ready to use H/W UART Interface 
	
	BSF   STATUS, RP0
	MOVLW B'11000000'  ;SET PC7 and PC8 as INPUTs using TRISC
	MOVWF TRISC
	
	MOVLW D'25' 	 
	MOVWF SPBRG 	  ;Save 25 to SPBRG for 9600 Baud Rate
	
	MOVLW B'00100110' ;Setup TXSTA for UART TX
	MOVWF TXSTA ;
	BSF TXSTA, TRMT

	BCF   STATUS, RP0
	
	MOVLW B'10110000'  
	MOVWF RCSTA 	  ;Setup RCSTA for UART RC
	
MainLoop	
	BTFSC PORTB, 4   ; Enter a value in h/w UART simulator to test RC
	GOTO MainLoop   
	
RcTxLoop	
	BTFSS PIR1, RCIF ; check if the input is ready in RCREG
	GOTO RcTxLoop
TxLoop	
	MOVF RCREG, W
	MOVWF TXREG
	BTFSC PIR1, TXIF
	GOTO TxLoop
	GOTO RcTxLoop

End	goto 	End	; superfluous

	