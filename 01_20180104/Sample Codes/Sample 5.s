MOV R1, #0x2000		;Initialize R1 = HEX 2000
MOV R3, #5			;Initialize R3 = 5
MOV R5, #20			;Initialize R5 = 20

LOOP1:
	STR R5, [R1]		;Store R5 @ address stored in R1
	ADD R5, R5, #1		;Increment R5 by 1
	ADD R1, R1, #4		;Increment R1 by 4 (i.e. next word which is 4 byte after current)
	SUBS R3, R3, #1		;Decrement R3 by 1 (update CPSR)
	BNE	LOOP1			;if (prev result != 0) branch to LOOP1

SUB R1, R1, #4		;Decrement R1 by 4

LOOP2:
	LDR R5, [R1]		;Load R5 with value store @ (address stored in R1)
	SUB R1, R1, #4		;Decrement R1 by 4
	ADD R3, R3, #1		;Increment R3 bt 1
	CMP R3, #5			;Compare R3 with 5
	BNE	LOOP2			;if (prev result == 0) i.e. R3 == 5, branch to LOOP2

END:
	B END			;Loopback to END