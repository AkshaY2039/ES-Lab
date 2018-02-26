@-------------------------------------------------------------------------------
	.equ SWI_Open,		0x66		;SWI code to open a file
	.equ SWI_RdInt,		0x6c		;SWI code to Read integer from file
	.equ SWI_Close,		0x68		;SWI code to close a file
	.equ SWI_Exit,		0x11		;SWI code to Halt Execution
	.global _START					;by default start at _START routine
@-------------------------------------------------------------------------------
OPEN:
	STMDB SP!, {LR}			;
	LDR R0, =File_Name		;store the File_Name into r0
	MOV R1, #0				;initialise r1 to 1(output mode)
	SWI SWI_Open			;open file
	LDR R1, =File_Handle	;use r1 to initialise File_Handle
	STR R0, [R1]			;store the file handle
	LDMIA SP!, {PC}			;
READ:
	STMDB SP!, {LR}			;
	LDR R0, =File_Handle	;
	LDR R0, [R0]			;
	SWI SWI_RdInt			;
	MOV R2, #10				;
	MUL R1, R0, R2			;
	LDR R0,	=File_Handle	;
	LDR R0,	[R0]			;
	SWI SWI_Close			;
	LDMIA SP!, {PC}			;
_START:
	BL OPEN					;
	BL READ					;
	BL LTIMER				;
	B EXIT					;
EXIT:
	SWI SWI_Exit			;
LTIMER:
	STMDB SP!, {LR}			;
HLTIMER:
	MOV R0, #0				;
	BL STIMER				;
	SUB R1, R1, #1			;
	CMP R1, #0				;
	BNE HLTIMER				;
	LDMIA SP!, {PC}			;
STIMER:
	STMDB SP!, {LR}			;
HSTIMER:
	ADD R0, R0, #1			;
	CMP R0, #199			;
	BNE HSTIMER				;
	LDMIA SP!, {PC}			;
;-------------------------------------------------------------------------------
File_Name: .asciz "timerinput.txt"	;Name of File that has input to timer
			.align
File_Handle: .word 1				;word aligned File_Handle at address 1
;-------------------------------------------------------------------------------