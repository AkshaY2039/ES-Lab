MOV r1, #0x2000 			 
MOV r3, #5
MOV r5, #20	

LOOP1:	
STR r5, [r1]
ADD r5, r5, #1
ADD r1, r1, #4
SUBS r3, r3, #1
BNE	LOOP1

SUB r1, r1, #4
LOOP2:	
LDR r5, [r1]
SUB r1, r1, #4
ADD r3, r3, #1
CMP r3, #5
BNE	LOOP2


END:
B END
	


