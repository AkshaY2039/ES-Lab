@----------------------------------------------------------------------------------------------------------------------------------------------------------------
@ This programs reads first 99 letters of each line of InputFile and copies it to OutputFile
@----------------------------------------------------------------------------------------------------------------------------------------------------------------
/*directives used*/
	.equ SWI_Open, 0x66			@SWI code to open a file (FileName = R0, File Mode = R1 (1 for Write, 0 for Read, 2 for Append), Output-> FileHandle in R0)
	.equ SWI_Close, 0x68		@SWI code to Close a file (FileHandle = R0)
	.equ SWI_Exit, 0x11			@SWI code to Halt Execution
	.equ SWI_PrStr, 0x69		@SWI code to print string to a File
	.equ SWI_RdStr, 0x6a		@SWI code to read string from a file
	.equ Display_String, 0x02	@SWi code to display string on STDOUT
	.global _START				@Program starts at _START sub routine (this routine name should start with '_')
@----------------------------------------------------------------------------------------------------------------------------------------------------------------

@sub-routine to open files
OPEN_FILES:
	LDR R0, =InFileName				@ set Name for input file
	MOV R1, #0						@ mode is input
	SWI SWI_Open					@ open file for input
	@BCS InFileError				@ if error ?
	LDR R5, =InFileHandle			@ load input file handle
	STR R0, [R5]					@ save the file handle
	LDR R0, =OutFileName			@ set Name for output file
	MOV R1, #1						@ mode is output
	SWI SWI_Open					@ open file for output
	@BCS OutFileError				@ if error ?
	LDR R4, =OutFileHandle			@ load output file handle
	STR R0, [R4]					@ save the file handle
	MOV PC, LR						@ Return to the instruction that called this routine as it address is stored in LR

@Main Routine of the Program
_START:
	BL OPEN_FILES					@ Call OPEN_FILES sub-routine
	LOOP:
		BL READ_FROM_IFILE				@ Call OPEN_FILES sub-routine
		CMP R6, #0						@ Compare R6 with 0
		BLNE DISPLAY_TO_STDOUT			@ if (R6 != 0), Call DISPLAY_TO_STDOUT sub-routine
		BLNE WRITE_TO_STDOUT			@ if (R6 != 0), Call WRITE_TO_STDOUT sub-routine
		BLNE WRITE_TO_OFILE				@ if (R6 != 0), Call WRITE_TO_OFILE sub-routine
		BNE LOOP						@ if (R6 != 0), Loopback
	BL CLOSE_FILES					@ Call CLOSE_FILES sub-routine
	B END							@ Branch to END routine

@sub-routine to read string from input file
READ_FROM_IFILE:
	LDR R0, =InFileHandle			@ Pointing R0 to input filehandle
	LDR R0, [R0]					@ Load the input filehandle back to R0
	LDR R1, =STRING					@ Load STRING address into R1 (destination address for Read String)
	MOV R2, #100					@ Move immediate 100 to R2 (max bytes to store)
	SWI SWI_RdStr					@ Read String form the file open R0 (file handle) R1 (destination address) R2 (max bytes to store)
	MOV R6, R0						@ Load values of R0 to R6 i.e. bytes read
	MOV PC, LR						@ Return to the instruction that called this routine as it address is stored in LR

@Display string on STDOUT
DISPLAY_TO_STDOUT:
	LDR R0, =STRING					@ Load the read string into R0
	SWI Display_String				@ Display contents of R0 to STDOUT
	LDR R0, =NEW_LINE				@ Load the NEW_LINE to R0
	SWI Display_String				@ Go to new line
	MOV PC, LR						@ Return to the instruction that called this routine as it address is stored in LR

@Write string to STDOUT (Same as display)
WRITE_TO_STDOUT:
	MOV R0, #1						@ file handle in R0, 1 is the value of file handle for STDOUT
	LDR R1, =STRING					@ Load the read string into R1
	SWI SWI_PrStr					@ Write the Contents of R1 to file open from R0 i.e. STDOUT
	LDR R1, =NEW_LINE				@ Load the NEW_LINE to R1
	SWI SWI_PrStr					@ Write the NEW_LINE to STDOUT
	MOV PC, LR						@ Return to the instruction that called this routine as it address is stored in LR

@sub-routine to write string to output file
WRITE_TO_OFILE:
	LDR R0, =OutFileHandle			@ Pointing R0 to output filehandle
	LDR R0, [R0]					@ Load the output filehandle back to R0
	LDR R1, =STRING					@ Load STRING into R1
	SWI SWI_PrStr					@ Write the Contents of R1 to file open from R0 (SWI_PrStr)
	CMP R6, #0						@ Compare R6 with 0
	LDRNE R1, =NEW_LINE				@ if (R6 != 0), Load the NEW_LINE to R1
	SWINE SWI_PrStr					@ if (R6 != 0), Write the NEW_LINE to output file
	MOV PC, LR						@ Return to the instruction that called this routine as it address is stored in LR

@sub-routine to close the files
CLOSE_FILES:
	LDR R0, =InFileHandle			@ Pointing R0 to input filehandle
	LDR R0, [R0]					@ Load the input filehandle back to R0
	SWI SWI_Close					@ Close input file
	LDR R0, =OutFileHandle			@ Pointing R0 to output filehandle
	LDR R0, [R0]					@ Load the output filehandle back to R0
	SWI SWI_Close					@ Close output file
	MOV PC, LR						@ Return to the instruction that called this routine as it address is stored in LR

@End Program Routine
END:
	SWI SWI_Exit		;Halt Execution

/*Labels being Uses*/
	InFileName:		.asciz "Infile1.txt"					;Name of Input file
@	InFileError:	.asciz "Unable to open input file\n"	;error message in case Input file doesn't open
					.align
	InFileHandle:	.word 0								;Declaring location for InFileHandle

	OutFileName:	.asciz "Outfile1.txt"					;Name of Output file
@	OutFileError:	.asciz "Unable to open output file\n"	;error message in case Output file doesn't open
					.align
	OutFileHandle:	.word 0								;Declaring location for OutFileHandle
	NEW_LINE:		.asciz "\n"								;to have a new line
	STRING: .skip 100									; allocate a size of 100 bytes (which is max that can be read by SWI_RdStr)