/*Label being Used*/
MyString: .asciz "Welcome to ARMSIM\n"	;ASCII string terminated by NULL

.equ Display_String, 0x02	;SWI code to Display String on STDOUT
.equ SWI_Exit, 0x11		;SWI code to Halt Execution

LDR R0, =MyString			;Load address of MyString into R0
SWI Display_String			;Display String to STDOUT

SWI SWI_Exit			;Halt Execution