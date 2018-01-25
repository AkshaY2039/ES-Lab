MOV r1,#5 		; Initialize register r1 = 5
MOV r0,#0 		; Initialize register r0 = 1
mov r2,#8   		; Initialize register r2 = 8
mov r4,#0x2000 		; Initialize r4 with 0x2000
LOOP:
ADD r3,r1,r0 		; r3 = r1 + r0
STR	r3,[r4]		; store r3 content at address 0x2000
ADD r0,r0,#1		; increment r0 by 1
ADD r4,r4,#4		; increment r4 by 4
CMP r0, r2		; compare r0 with r2
NOP
NOP
BEQ END			; if r0 == r2 go to END 
B LOOP			; else back to loop
NOP
NOP
END:			; start of end loop			
SWI 0X11
