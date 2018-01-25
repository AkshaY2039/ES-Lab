MOV r1,#5 	; Initialize register r1 = 5
MOV r0,#3 	; Initialize register r0 = 3
mov r2,#8
LOOP:
ADD r1,r2,r0 	; r1 = r2 + r0
SUBS r0,r0,#1 	; r0  = r0-1
BEQ END		; if previous result != 0 branch to B 
B LOOP
NOP
NOP
NOP
END:			; start of end loop
NOP
NOP
NOP 			; end
B END
