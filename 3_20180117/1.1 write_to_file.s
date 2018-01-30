/*
Embedded Systems Lab 3 - 17-01-2018
	Assignment 1.1 : Write to a File
					Write an ARM assembly program to WRITE to a file. Write 2 or more lines of text to this
					file. Make sure you close the file after you write to it.
		-- Akshay Kumar	(CED15I031)
*/

/*DATA SECTION*/
	/*labels being used*/
	O_FILE: .asciz "File1.txt"												;Name of the output file to write to (.asciz for ASCII string terminateed with NULL)
			.align
	STRING1: .asciz "This is the line 1. Successfully writing to file.\n"	;String 1 to be written
			.align
	STRING2: .asciz "This is the line 2. Ends the file."					;String 2 to be written
			.align
	O_FILE_HANDLE: .word 0													;Declaring location for filehandle

	/*directives definition*/
	.equ Open_File, 0x66		;SWI_Open to open file
	.equ Print_String, 0x69		;SWI_Prstr to print string
	.equ Close_File, 0x68		;SWI_Close to close file
	.equ Halt_Exec, 0x11		;SWI_Exit to halt execultion
	.equ FILE_MODE, 1			;0 represents write/output mode

LDR R0, =O_FILE			;Load output file name into R0
MOV R1, #FILE_MODE		;Move immediate 1 into R1, since 1 represents OUTPUT mode, 0 represents INPUT mode.

SWI Open_File			;Open file based on filename in R0 and mode in R1 (SWI_Open)
	LDR R5, =O_FILE_HANDLE	;Assign a the address 0
	STR R0, [R5]			;Store filehandle to R5
	LDR R1, =STRING1		;Load STRING1 into R1
	SWI Print_String		;Write the Contents of R1 to file open from R0 (SWI_PrStr)
	LDR R1, =STRING2		;Load STRING2 into R1
	SWI Print_String		;Write the Contents of R1 to file open from R0 (SWI_PrStr)
	LDR R0, =O_FILE_HANDLE	;Pointing R0 to filehandle
	LDR R0, [R0]			;Load the filehandle back to R0
SWI Close_File			;Close File (SWI_Close) R0 as file handle

SWI Halt_Exec			;Halt execultion (SWI_Exit)