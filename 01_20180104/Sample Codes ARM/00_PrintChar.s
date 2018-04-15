@------------------------------------------------------------------------------------------------
@ This program is an example for printing character to STDOUT
@------------------------------------------------------------------------------------------------

.equ SWI_PrChr, 0x00		;SWI for printing character to STDOUT

MOV R0, #'A			;Move character 'A' into R0
SWI SWI_PrChr		;Print character to STDOUT
MOV R0, #'\n		;Move character '\n' into R0
SWI SWI_PrChr		;Print character to STDOUT

SWI 0x11			;Halt Execution/Exit (without this, program counter will go out of Valid Memory Range due)