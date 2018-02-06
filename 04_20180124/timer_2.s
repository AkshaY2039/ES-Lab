.equ sec1, 1000
.equ point1sec, 100
.equ embestTimerMask, 0x7fff
.equ top15bitRange, 0x0000ffff
.equ SWI_GetTicks, 0x6d
.equ SWI_EXIT, 0x11

.text

_start:
    mov r6,#0
    ldr r8,=top15bitRange
    ldr r7,=embestTimerMask
    ldr r10,=point1sec
    SWI SWI_GetTicks
    mov r1,r0
    and r1,r1,r7
RepeatTillTime:
    add r6,r6,#1
    SWI SWI_GetTicks
    mov r2,r0
    and r2,r2,r7
    cmp r2,r1
    bge simpletime
    sub r9,r8,r1
    add r9,r9,r2
    bal checkInt
simpletime:
    sub r9,r2,r1
checkInt:
    cmp r9,r10
    blt RepeatTillTime
    swi SWI_EXIT
    .end