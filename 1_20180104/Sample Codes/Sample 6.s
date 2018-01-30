MOV R1, #0x1500	;Base Register for memory address
MOV R5, #20		;Content To Store
MOV R2, #10		;Number Of Times to Store (Loop Counter)

LOOP1:
	STR R5, [R1, #4]!	;Store value of R5 @ (address stored in R1 + 4)th byte (Pre-indexing)
	ADD R5, R5, #2		;Increment R5 by 2
	SUBS R2, R2, #1		;Decrement R2 by 1 (Update CPSR)
	BNE	LOOP1			;if (prev result != 0) Loopback to LOOP1

MOV R2, #10		;Number Of Times to Store (Loop Counter)
MOV R1, #0x1500	;Base Register for memory address

LOOP2:
	STR R5, [R1], #4	;Store value of R5 @ (address stored in R1) then increment R1 by 4 (Post-indexing)
	ADD R5, R5, #2		;Increment R5 by 2
	SUBS R2, R2, #1		;Decrement R2 by 1 (Update CPSR)
	BNE	LOOP2			;if (prev result != 0) Loopback to LOOP2

SWI 0x11		;Halt Execution