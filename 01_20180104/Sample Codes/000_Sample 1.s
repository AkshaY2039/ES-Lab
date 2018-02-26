@---------------------------------------------------------------------------------------------------------------------------
@ This program is an example for Add, Branch, Subtract, Move and Looping
@---------------------------------------------------------------------------------------------------------------------------

MOV R0, #3		;Initialize R0 = 3 (Loop index/variable)
MOV R2, #8		;Initialize R2 = 8

LOOP:
	ADD R1, R2, R0		;R1 = R2 + R0
	SUBS R0, R0, #1		;R0 = R0 + 1 (and update CPSR)
	BEQ END				;IF Preious Result == 0 branch to END
	B LOOP				;Loopback to LOOP

END:
	B END				;Loopback to END