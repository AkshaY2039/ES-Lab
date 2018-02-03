/*
Embedded Systems Lab 5 - 31-01-2018
	Assignment 1.5 : LED Alternate
					Write ARM assembly code that can make the two red LEDs in Embest Plugin of ARMSIM to glow alternatively at 
					observable rate. Your code should be user configurable for various rate. User timer developed in problem 4.
		-- Akshay Kumar	(CED15I031)
	Note: To Modify The Rate of Alternation, change the value of LT counter appropriately
*/

/*DATA SECTION*/
	/*labels being used*/
	.equ STCounter,	250		;Short timer counter as 250 (as SUB takes 1 cycle and Branch takes 3 cycles)
	.equ LTCounter,	1000		;Large timer counter
	.equ RIGHT_LED,	2		;2 as in 10 in binary (Only Right ON)
	.equ LEFT_LED,	1		;1 as in 01 in binary (Only Left ON)
	.equ LED_GLOW,	0x201	;SWI code to pass R0 to LED in Embest Plugin

LED_PATTERN:
	MOV R0, #RIGHT_LED	;To Turn On RIGHT_LED
	SWI LED_GLOW		;GLOW LED
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	MOV R0, #LEFT_LED	;To Turn On LEFT_LED
	SWI LED_GLOW		;GLOW LED
	MOV R5, PC			;Store Address of Program Counter into R5 (which points to 2nd Instruction Ahead due to 3 stage Pipelining)
	B L_TIMER			;Delay
	B LED_PATTERN		;Loopback to LED_PATTERN

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