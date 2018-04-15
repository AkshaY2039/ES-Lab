@------------------------------------------------------------------------------------------------
@ This program is an example for addressing in simple logic of addition to a stored memory
@ location and then referring to it.
@------------------------------------------------------------------------------------------------

/*DATA SECTION*/
	/*Directives*/
	.equ Halt_Exec, 0x11		;Deifne Halt_Exec as 0x11 i.e. SWI_Halt

MOV R1, #5			;Initialize R1 = 5
MOV R0, #0			;Initialize R0 = 0 (Loop Counter)
MOV R2, #8			;Initialize R2 = 8 (Halting value of Loop Counter)
MOV R4, #0x2000		;Initialize R4 with HEX 2000 (location for storing sum)

LOOP:
	ADD R3, R1, R0		;R3 = R1 + R0
	STR R3, [R4]		;Store R3 content at address HEX 2000 as R4 stores that address
	ADD R0, R0, #1		;Increment R0 by 1
	ADD R4, R4, #4		;Increment R4 bt 4 so that the next address is next word
	CMP R0, R2			;Compare R0 with R2
	BEQ END				;if R0 == R2 goto END
	B LOOP				;Goto Loop

END:
	SWI Halt_Exec		;Halt Execution