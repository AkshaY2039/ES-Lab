@-------------------------------------------------------------------------------------------------------
@ This program is an example for Subroutine to check for an interval with a 15‐bit timer (Embest Board)
@-------------------------------------------------------------------------------------------------------

/*
	".data" driective switches current section to Data Section
	Data Section is used for storing all kind of various data, which will be copied to RAM when the program starts
*/
.data
	.equ sec1,				1000 		@ 1 seconds interval
	.equ point1Sec,			100			@ 0.1 seconds interval
	.equ embestTimerMask,	0x7fff		@ 15 bit mask for timer values
	.equ top15bitRange,		0x0000ffff	@ (2^15) -1 = 32,767
	.equ SWI_GetTicks,		0x6d		@ SWI code to get current time as ticks
	.equ SWI_Exit,			0x11		@ SWI code to halt execution

/*
	".text" driective switches current section to Text Section
	Text Section is used to store the code. This usually gets stored in the flash memory of microcontroller
	but can be put somewhere else by customizing the linker-script
*/
.text
	_START:					@ _START routine to start with
		MOV R6, #0					@ R6 = 0, to make the loops continue
		LDR R8, =top15bitRange		@ R8 = 32767
		LDR R7, =embestTimerMask	@ R7 = Timer Mask
		LDR R10, =point1sec			@ 
		SWI SWI_GetTicks			@ 
		MOV R1, R0					@ 
		AND R1, R1, R7				@ 

	REPEAT_TILL_TIME:		@ subroutine repeat till a given time
		ADD R6, R6, #1				@ 
		SWI SWI_GetTicks			@ 
		MOV R2, R0					@ 
		AND R2, R2, R7				@ 
		CMP R2, R1					@ 
		BGE SIMPLE_TIME				@ 
		SUB R9, R8, R1				@ 
		ADD R9, R9, R2				@ 
		BAL CHECK_INT				@ 

	SIMPLE_TIME:			@ Simplify time Subroutine
		SUB R9, R2, R1				@ 

	CHECK_INT:				@ Check Interval Subroutine
		CMP R9, R10					@ 
		BLT REPEAT_TILL_TIME		@ 
		SWI SWI_Exit				@ 

	.END