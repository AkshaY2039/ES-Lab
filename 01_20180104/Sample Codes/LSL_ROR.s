MOV R0, #2				;Initialize R0 = 2
MOV R1, #20				;Initialize R1 = 20
NOP						;No Operation
ADD R3, R1, R0, LSL #3	;R3 = R1 + (R0 after LSL [Logical Shift Left] by 3b i.e. multiply by 8)
ADD R3, R1, R1, ROR #4	;R3 = R1 + (R1 after ROR [Rotate Right] by 4b)
NOP						;No Operation
MOV R4, #0x100			;Initialize R4 = 256 (0x100) 
MOV R5, R4, ROR #16		;Assign R5 = (ROR R4 by 16b)