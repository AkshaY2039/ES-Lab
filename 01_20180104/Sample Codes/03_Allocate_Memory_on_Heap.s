MOV R0, #20			@get 20 bytes (comments can also be written using ';' or @ AND '/*...*/' for multiline)
SWI SWI_MeAlloc		;Allocate 20 bytes in the Heap
LDR R1, =Address	;Load contents of label Address into R1
STR R0, [R1]		;Store Address stored in R0 to R1
SWI SWI_DAlloc		;DeAllocate all memory form the Heap

SWI SWI_Exit		;Halt Execution

/*It is a good practice to keep LABELS at the end so that the 
 working routines don't make Program Counter go beyond the Valid Range of Memory in ARMSIM*/
/* While equ directives can be keeping in end doesn't make ANY difference*/
	Address: .word 0	;Declaring Word aligned location

	.equ SWI_Exit, 0x11		;SWI code to Halt Execution
	.equ SWI_MeAlloc, 0x12	;SWI code for allocating Block of Memory on Heap
	/*Obtain a new block of memory from the heap area of the program space. If no more memory is
	available, the special result ‐1 is returned and the C bit is set in the CPSR*/
	.equ SWI_DAlloc, 0x12	;SWI code for de-allocating all blocks of memory form Heap
	/*Causes all previously allocated blocks of memory in the heap area to be considered as deallocated
	(thus allowing the memory to be reused by future requests for memory blocks).*/