/*
Embedded Systems Lab 5 - 31-01-2018
	Assignment 1.6 : 0 to 9 in 8 Segment
					Write ARM assembly code that can make the 8-segment display to go from 0 to 9 at an observable rate. Your code 
					should be user configurable for various rate.
		-- Akshay Kumar	(CED15I031)0
	Relation of Codes for the Digits assigned:
		Alignment of bits : | A | B | C | P | D | E | F | G |
		Connection in 8 Segment Display:
				 ___A___
				|       |
			  G	|       | B
				|___F___|
				|       |
			  E	|       | C
				|___D___|  . P

	Note: To Modify The Rate of change, change the value of LT counter appropriately
*/

/*DATA SECTION*/
	/*labels being used*/
	.equ STCounter,	250		;Short timer counter as 250 (as SUB takes 1 cycle and Branch takes 3 cycles)
	.equ LTCounter,	1000		;Large timer counter
	.equ SEG_DISPLAY, 0x200	;SWI code to pass R0 to 8 SEGMENT Display in Embest Plugin
	.equ ZERO,	0xED		;8 Segment code for 0
	.equ ONE,	0x60 		;8 Segment code for 1
	.equ TWO,	0xCE 		;8 Segment code for 2
	.equ THREE,	0xEA 		;8 Segment code for 3
	.equ FOUR,	0x63 		;8 Segment code for 4
	.equ FIVE,	0xAB		;8 Segment code for 5
	.equ SIX,	0xAF 		;8 Segment code for 6
	.equ SEVEN,	0xE0 		;8 Segment code for 7
	.equ EIGHT,	0xEF 		;8 Segment code for 8
	.equ NINE,	0xEB 		;8 Segment code for 9

SEG_8_1to9:
	MOV R0, #ZERO		;To Display 0
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #ONE		;To Display 1
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #TWO		;To Diaplay 2
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #THREE		;To Display 3
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #FOUR		;To Display 4
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #FIVE		;To Display 5
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #SIX		;To Display 6
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #SEVEN		;To Display 7
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #EIGHT		;To Display 8
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #NINE		;To Display 9
	SWI SEG_DISPLAY		;GLOW 8-Segment Display
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	B SEG_8_1to9		;Loopback to SEG_8_1to9

L_TIMER:
	MOV R2, #LTCounter	;Initialize R2 by LTCounter
	L_LOOP:
		BL S_TIMER			;Branch with Link to S_TIMER
		SUBS R2, R2, #1		;Decrement R2 by 1
		BNE L_LOOP			;if R2 != 0, Loopback to L_LOOP
		MOV PC, R5			;Move the address in R5 to Program Counter i.e. PC will now go back to the statement which called this routine

S_TIMER:
	MOV R1, #STCounter	;Initialize R1 by STCounter
	S_LOOP:
		SUBS R1, R1, #1		;Decrement R1 by 1
		BNE S_LOOP			;if R1 != 0, Loopback to S_LOOP
		MOV PC, LR			;Move the address in Link Register to Program Counter i.e. PC will now go back to the statement which called this routine