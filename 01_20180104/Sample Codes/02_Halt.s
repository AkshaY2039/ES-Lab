@------------------------------------------------------------------------------------------------
@ This program is an example for Halt Execution
@------------------------------------------------------------------------------------------------

.equ SWI_Exit, 0x11		;SWI code to Halt Execution

SWI SWI_Exit			;Halt Execution