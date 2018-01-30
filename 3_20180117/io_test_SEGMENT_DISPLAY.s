/*DATA Section*/
	/*directives*/
	.equ SEG_A, 0x80		;
	.equ SEG_B, 0x40		;
	.equ SEG_C, 0x20		;
	.equ SEG_D, 0x08		;
	.equ SEG_E, 0x04		;
	.equ SEG_F, 0x02		;
	.equ SEG_G, 0x01		;
	.equ SEG_P, 0x10		;

	/*Labels*/
	Digits:
		.word SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G			@0
		.word SEG_B | SEG_C											@1
		.word SEG_A | SEG_B | SEG_F | SEG_E | SEG_D					@2
		.word SEG_A | SEG_B | SEG_F | SEG_C | SEG_D					@3
		.word SEG_G | SEG_F | SEG_B | SEG_C							@4
		.word SEG_A | SEG_G | SEG_F | SEG_C | SEG_D					@5
		.word SEG_A | SEG_G | SEG_F | SEG_E | SEG_D | SEG_C			@6
		.word SEG_A | SEG_B | SEG_C									@7
		.word SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G	@8
		.word SEG_A | SEG_B | SEG_F | SEG_G | SEG_C					@9
		.word 0														@Blank display

STMFD SP!, {R0 - R2, LR}	;
LDR R2, =Digits				;
LDR R0, [R2, R0, LSL #2]	;
TST R1, #0x01				;IF R1 = 1,
ORRNE R0, R0, #SEG_P		;ORR if R1 != 1 R0 with SEG'P'
SWI 0x200					;
LDMFD SP!, {R0 - R2, PC}	;
SWI 0x200					;
	


