;-------------------------------------------------------------------------------
  .equ pr_stdout,0x69                     ;replace pr_stdout with 0x00
  .equ file_open,0x66                     ;replace file_open with 0x66
  .equ file_write,0x6b                    ;replace file_write with 0x69
  .equ file_read,0x6c                     ;replace file_read with 0x69
  .equ file_close,0x68                    ;replace file_close with 0x68
  .equ exit,0x11                          ;replace exit with 0x11
  .equ pr_ch,0x00
  .equ light_up,0x201
  .equ black_button,0x202
  .global _start
;-------------------------------------------------------------------------------
Open:
  stmdb sp!,{lr}
  ldr r0,=filename                        ;store the filename into r0
  mov r1,#0                               ;initialise r1 to 1(output mode)
  swi file_open                           ;open file
  ldr r1,=filehandle                      ;use r1 to initialise filehandle
  str r0,[r1]                             ;store the file handle
  ldmia sp!,{pc}
Read:
  stmdb sp!,{lr}
  ldr r0,=filehandle
  ldr r0,[r0]
  swi file_read
  mov r2,#10
  mul r1,r0,r2
  ldr r0,=timerlength
  str r1,[r0]
  ldr r0,=filehandle
  ldr r0,[r0]
  swi file_close
  ldmia sp!,{pc}
_start:
  bl Open
  bl Read
  bl Light
  b EXIT
EXIT:
  swi exit
Light:
  stmdb sp!,{lr}
Hlight:
  mov r0,#1
  swi light_up
  bl Ltimer
  mov r0,#0
  swi light_up
  mov r0,#2
  swi light_up
  bl Ltimer
  swi black_button
  cmp r0,#1
  bne Hlight
  ldmia sp!,{pc}
Ltimer:
  stmdb sp!,{lr}
  ldr r1,=timerlength
  ldr r1,[r1]
Hltimer:
  mov r0,#0
  bl Stimer
  sub r1,r1,#1
  cmp r1,#0
  bne Hltimer
  ldmia sp!,{pc}
Stimer:
  stmdb sp!,{lr}
Hstimer:
  add r0,r0,#1
  cmp r0,#199
  bne Hstimer
  ldmia sp!,{pc}
;-------------------------------------------------------------------------------
timerlength: .skip 4
.align
filename: .asciz "timerinput.txt"
.align
filehandle: .skip 4