MOV r1,#5 	; Initialize register r1 = 5
MOV r0,#3 	; Initialize register r0 = 3
LOOP:
ADD r1,r1,r0 	; r1 = r1 + r0
SUBS r0,r0,#1 	; r0  = r0-1
BEQ END
B LOOP		
NOP
NOP
NOP
END:			; start of end loop
NOP
NOP
NOP
B END