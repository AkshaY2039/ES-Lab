/*directives used*/
	.equ SWI_Open, 0x66			@SWI code to open a file (FileName = R0, File Mode = R1 (1 for Write, 0 for Read, 2 for Append), Output-> FileHandle in R0)
	.equ SWI_Close, 0x68		@SWI code to Close a file (FileHandle = R0)
	.equ SWI_Exit, 0x11			@SWI code to Halt Execution
	.equ SWI_PrStr, 0x69		@SWI code to print string to a File
	.equ SWI_RdStr, 0x6a		@SWI code to read string from a file
	.equ Display_String, 0x02	@SWi code to display string on STDOUT

LDR R0, =InFileName				@ set Name for input file
MOV R1, #0						@ mode is input
SWI SWI_Open					@ open file for input
@BCS InFileError				@ if error ?
LDR R5, =InFileHandle			@ load input file handle
STR R0, [R5]					@ save the file handle
LDR R1, =STRING					@ Load STRING address into R1 (destination address for Read String)
MOV R2, #100					@ Move immediate 100 to R2 (max bytes to store)
SWI SWI_RdStr					@ Read String form the file open R0 (file handle) R1 (destination address) R2 (max bytes to store)
LDR R0, =STRING					@ Load the Read string into R0
SWI Display_String				@ Display contents of R0 to STDOUT

LDR R0, =OutFileName			@ set Name for output file
MOV R1, #1						@ mode is output
SWI SWI_Open					@ open file for output
@BCS OutFileError				@ if error ?
LDR R4, =OutFileHandle			@ load output file handle
STR R0, [R4]					@ save the file handle
LDR R1, =STRING					@ Load STRING into R1
SWI SWI_PrStr					@ Write the Contents of R1 to file open from R0 (SWI_PrStr)

LDR R0, =InFileHandle			@ Pointing R0 to input filehandle
LDR R0, [R0]					@ Load the input filehandle back to R0
SWI SWI_Close					@ Close input file
LDR R0, =OutFileHandle			@ Pointing R0 to output filehandle
LDR R0, [R0]					@ Load the output filehandle back to R0
SWI SWI_Close					@ Close output file

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
	STRING: .skip 100									; allocate a size of 100 bytes