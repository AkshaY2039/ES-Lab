MOV r1, #0x1500	; base register			 
MOV r5, #20		; Content to store
MOV r2, #10		; number of items to store	

LOOP1:	
STR r5, [r1, #4]!	; pre-index 
ADD r5, r5, #2
SUBS r2, r2, #1
BNE	LOOP1

MOV r2, #10
MOV r1, #0x1500
LOOP2:	
STR r5, [r1], #4	; post-index
ADD r5, r5, #2
SUBS r2, r2, #1
BNE	LOOP2

END:
B END
	


