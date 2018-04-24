TXBUFF	equ	0x22
RXBUFF	equ	0X23
SDA	equ	0x4
SCL	equ	0x3
DEVADD	equ 	B'10100000'
INTADD	equ	B'00000000'
DATA	equ	B'01100000'


Main	call 	I2CIn
	call 	I2COut
End	nop
	goto	End
	
I2CIn	
	call	Start		; Generate START condition
	movlw	DEVADD		; Send peripherals address with R/W = 0 (write)
	call	TX		
	movlw	INTADD 		; Send 'peripheral's internal address
	call	TX	
	call	ReStart
	movlw	DEVADD
	iorlw	B'00000001'
	call	TX
	bsf	TXBUFF,7
	call	RX	
	movlw	DATA	 	; Send data to write to periphera	
	call	Stop		; Generate STOP condition
	return	

I2COut
	
	call	Start		; Generate START condition
	movlw	DEVADD		; Send peripherals address with R/W = 0 (write)
	call	TX		
	movlw	INTADD 		; Send 'peripheral's internal address
	call	TX		
	movlw	DATA	 	; Send data to write to peripheral
	call	TX		
	call	Stop		; Generate STOP condition
	return	

; The Start subroutine initializes the 12C bus and then 					
; generate the START condition on he 12C bus. The ReStart				
; entry point bypasses the initialization of the 12C bus.					
					
Start					
	movlw	B'00111011'	;Enable 12C master mode	
	movwf	SSPCON			
	bcf	PORTC,SDA	;Drive SDA low when it is an ouput	
	bcf	PORTC,SCL	;Drive SCL low when it is an ouput	
	movlw	TRISC		;Set indirect pointer to TRISC	
	movwf	FSR			
					
ReStart					
	bsf	INDF, SDA	;Make sure SDA is high	
	bsf	INDF, SCL	;Make sure SCL is high	
	bcf	INDF, SDA				
	bcf	INDF, SCL			
	return				
		
; The Stop subroutine generates the STOP condition on the 12C bus.				
				
Stop				
	bcf	INDF,SDA	;Return SDA low
	bsf	INDF,SCL	;Drive SCL high
	bsf	INDF,SDA	;and then drive SDA high
	return			

; The TX subroutine sends out the byte passed to it in W.					
; It returns with Z=1 if ACK occurs.					
; It returns with Z=0 if NOACK occurs.					
TX					
	movwf	TXBUFF		;Save parameter in TXBUFF	
	bsf	STATUS,C	;Rotate a one through TXBUFF to count bits	
TX_1					
	rlf	TXBUFF, F	;Rotate TXBUFF left, through Carry	
	movf	TXBUFF,F	;Set z bit when all eight bits have been transferred	
	btfss	STATUS,Z	;Until Z=1	
	call	BitOut		;send Carry bit, then clear Carry bit	
	btfss	STATUS,Z	;	
	goto	TX_1		;then do it again	
	call	BitIn		;Read acknowledge bit inot bit 0 of RXBUFF	
	movlw	B'00000001'	; Check acknowledge bit	
	andwf	RXBUFF,W	; Z=1 if ACK; Z=0 if NOACK	
	return				

; The BitOut subroutine transmits, then clears, the Carry bit				
BitOut				
	bcf	INDF, SDA	;Clear SDA
	btfsc	STATUS,C	;skip next if C is 0
	bsf	INDF, SDA	;else light up SDA!
	bsf	INDF, SCL	;Pulse clock line
	bcf	INDF,SCL	;depulse the clock line
	bcf	STATUS,C	;Clear Carry bit
	return			
	
RX
	movlw	B'00000001'
	movwf	RXBUFF
RX-1
	rlf	RXBUFF,F
	call	BitIn
	btfss	STATUS,C
	goto 	RX-1
	rlf	TXBUFF,F
	call	BitOut
	movf	RXBUFF,W
	return

;The BitIn subroutine receives one bit into bit 0 of RXBUFF					
BitIn					
	bsf	INDF,SDA	;Relase SDA line	
	bsf	INDF,SCL	;Drive clock line high	
	bcf	RXBUFF,0	;Copy SDA to bit 0 of RXBUFF	
	btfsc	PORTC, SDA			
	bsf	RXBUFF,0			
	bcf	INDF, SCL	;Drive clock line low again	
	return				
; ; ; ; ; ; 	End of 12C subroutines ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;; ; ; ; ;;  ; ; ; ; ; ; ;  				
