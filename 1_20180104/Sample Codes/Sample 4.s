MOV R1, #5 			; Initialize R1 = 5
MOV R3, #10			; Initialize R3 = 10

ADD R0, R1, R1, LSL #4	; R0 = R1*17 i.e. R1 + R1*16 (Logical Left Shift by 4b)
	
RSB R2, R3, R3, LSL #4	; R2 = R3*15 i.e. R3*16 - R3 as Reverse Subtract
RSB R2, R2, R2, LSL #3	; R2 = R2*7 i.e. R2*8 - R2 as Reverse Subtract

SWI 0x11				; SWI_Halt to Halt Execution