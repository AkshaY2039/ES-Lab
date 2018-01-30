MOV R0, #10			;Initialize R0 = 10 (Loop Counter)
MOV R1, #10			;Initialize R1 = 10
MOV R2, #0x2000		;Initialize R2 = HEX 2000 (for address to store R1)

LOOP:
	STR R1, [R2, #4]	;Store R1's value into [(Address in R2) + 4]th byte
	ADD R1, R1, #1		;R1 = R1 + 1
	SUBS R0, R0, #1		;R0 = R0 - 1 (update CPSR)
	BNE LOOP			;If previous result != 0 Loopback

SWI 0x11			;SWI_Halt to Halt Execution