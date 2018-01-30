MOV R0, #2			;2 as in 10 in binary
SWI 0x201			@ LEFT LED ON (0x201 for passing to LED plugin)
MOV R0, #1			;1 as in 01 in binary
SWI 0x201			@ RIGHT LED ON
MOV R0, #3			;3 as in 11 in binary
SWI 0x201			@ BOTH LEDS ON
SWI 0x11			; Halt Execution