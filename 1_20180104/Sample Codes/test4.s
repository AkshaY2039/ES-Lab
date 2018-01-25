MOV r1, #5 			; Initialize register r1 = 5
MOV r3, #10		
ADD r0, r1, r1, LSL #4	; r1*17
NOP	
RSB r2, r3, r3, LSL #4	; r2 = r3 * 15
RSB r2, r2, r2, LSL #3	; r2 = r2 * 7
NOP
END:
B END
	


