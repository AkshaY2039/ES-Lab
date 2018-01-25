/*
Embedded Systems Lab 3 - 17-01-2018
	Assignment 1.3 : Read integer from a File
					Write an ARM assembly program to receive 3 different Integers (Comma separated) 
					inputs from a file. After receiving all the three values, print them on STDOUT 
					on separate lines.
		-- Akshay Kumar	(CED15I031)
*/

/*DATA SECTION*/
	/*labels being used*/
	I_FILE: .asciz "Integer.txt"	;Name of the input file to read from
			.align
	CHAR_BUFF: .word 80				;

	/*directives definition*/
	.equ Open_File, 0x66		;SWI_Open to open file
	.equ Read_String, 0x6a		;SWI_Rdstr to read string
	.equ Close_File, 0x68		;SWI_Close to close file
	.equ Halt_Exec, 0x11		;SWI_Exit to halt execultion			
	.equ Display_Char, 0x00		;SWI_PrChr to display character on STDOUT
	.equ Display_String, 0x02	;to display string on STDOUT
	.equ FILE_MODE, 0			;0 represents read/input mode

LDR R0, =I_FILE			;Load input file name into R0
LDR R1, =FILE_MODE		;Load value of FILE_MODE into R1

SWI Open_File			;Open file based on filename in R0 and mode in R1 (SWI_Open)
	LDR R1, =CHAR_BUFF		;
	MOV R2,	#80				;
	SWI Read_String			;Read String form the file open R0 (file handle) R1 (destination address) R2 (max bytes to store)
	LDR R0, =CHAR_BUFF		;Load the Read string into R0
	SWI Display_String		;Display contents of R0 to STDOUT
SWI Close_File			;Close File (SWI_Close) R0 as file handle

MOV R0, #10				;
SWI Display_Char		;
MOV R0, #10				;
SWI Display_Char		;

LOOP:
	LDRB R0, [R1], #1	;Read Byte by Byte from R1
	CMP R0, #44			;Compare if R0 == ','
	BEQ CHANGE			;
	CMP R0, #0			;
	BEQ END				;If the PC = 0 branch to END
	SWI Display_Char	;Display the Character
	B LOOP				;Branch to LOOP (Repeat LOOP)

CHANGE:
	MOV R0, #10			;
	SWI Display_Char	;
	B LOOP				;

END:
	SWI Halt_Exec			;Halt execultion (SWI_Exit)