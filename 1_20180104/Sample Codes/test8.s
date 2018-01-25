

.equ SEG_A,0x80
.equ SEG_B,0x40
.equ SEG_C,0x20
.equ SEG_D,0x08
.equ SEG_E,0x04
.equ SEG_F,0x02
.equ SEG_G,0x01
.equ SEG_P,0x10

Digits:
.word SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_G @0
.word SEG_B|SEG_C @1
.word SEG_A|SEG_B|SEG_F|SEG_E|SEG_D @2
.word SEG_A|SEG_B|SEG_F|SEG_C|SEG_D @3
.word SEG_G|SEG_F|SEG_B|SEG_C @4
.word SEG_A|SEG_G|SEG_F|SEG_C|SEG_D @5
.word SEG_A|SEG_G|SEG_F|SEG_E|SEG_D|SEG_C @6
.word SEG_A|SEG_B|SEG_C @7
.word SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G @8
.word SEG_A|SEG_B|SEG_F|SEG_G|SEG_C @9
.word 0 @Blank display

mov r0,#0x02
swi 0x201 @ left LED on
mov r0,#0x01
swi 0x201 @ right LED on
mov r0,#0x03
swi 0x201 @ both LEDs on

stmfd sp!,{r0-r2,lr}
ldr r2,=Digits
ldr r0,[r2,r0,lsl#2]
tst r1,#0x01 @if r1=1,
orrne r0,r0,#SEG_P @then show “P”
swi 0x200
ldmfd sp!,{r0-r2,pc}
swi 0x200
	


