mov r0, #10
mov r1, #10
mov r2, #0x2000
mov r4, #4
SLOOP:
str  r1, [r2, #4]
add r1, r1, #1
subs r0, r0, #1
bne SLOOP
swi 0x11

