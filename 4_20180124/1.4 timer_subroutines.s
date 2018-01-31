/*
Embedded Systems Lab 4 - 24-01-2018
	Assignment 1.4 : Timer Sub Routines
					In some single threaded embedded system applications, we use timers built using assembler sub-routine.
					This type of routines is sufficient and reasonably accurate for many applications. Develop a 
					sub-routine “Stimer” that can create 1000(approximately)Clock cycles delay. Using this subroutine 
					write another sub-routine “Ltimer” that can create delay which are multiples of 10000 (approximately) 
					cycles. The Ltimer is simple and no need to other timers.The Ltimer can be used to create periodic scan of I/O devices or any periodic activity.
		-- Akshay Kumar	(CED15I031)
		Approach : Simple Loop Routines... Nested Loop
*/

/*DATA SECTION*/
	/*labels being used*/
	.equ STCounter, 250		;Short timer counter as 250 (as SUB takes 1 cycle and Branch takes 3 cycles)
	.equ LTCounter, 10		;Large timer counter as 10 (multiple of STCounter)
	.equ HaltExec, 0x11		;SWI code for Halt Execution

L_TIMER:
	MOV R2, #LTCounter	;Initialize R2 by LTCounter
	L_LOOP:
		BL S_TIMER			;Branch with Link to S_TIMER
		SUBS R2, R2, #1		;Decrement R2 by 1
		BNE L_LOOP			;if R2 != 0, Loopback to L_LOOP

SWI HaltExec		;Halt Execution

S_TIMER:
	MOV R1, #STCounter	;Initialize R1 by STCounter
	S_LOOP:
		SUBS R1, R1, #1		;Decrement R1 by 1
		BNE S_LOOP			;if R1 != 0, Loopback to S_LOOP
		MOV PC, LR			;Move the address in Link Register to Program Counter i.e. PC will now go back to the statement which called this routine