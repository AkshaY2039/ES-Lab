ldr r0,=OutFile
mov r1,#0
swi 0x66
ldr r1,=OutFileHandle
str r0,[r1]

ldr r1,=Read
mov r2,#10
swi 0x6a
swi 0x02

loop:
mov r0, #'\n
swi 0x00
ldrb r0,[r1],#1
cmp r0,#',
BEQ jmp
swi 0x00
jmp:
cmp r0,#0
BNE loop

@mov r0,#1
@swi 0x69

ldr r0,=OutFileHandle
str r0,[r0]
swi 0x68
swi 0x11

OutFile: .asciz "Integer.txt"
Read: .skip 80
OutFileHandle: .word 0