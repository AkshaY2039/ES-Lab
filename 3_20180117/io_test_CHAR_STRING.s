/*DATA SECTION*/
	/*Labels*/
	String: .asciz "Its ES Lab" ;String to be displayed
			.align

	/*directives*/
	.equ PrChr, 0		;SWI code 0 for printing character to STDOUT
	.equ PrStr, 0x02	;to display string on STDOUT

MOV R0, #72		;Assign R0 = 'H' ASCII(72)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #69		;Assign R0 = 'E' ASCII(69)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #76		;Assign R0 = 'L' ASCII(76)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #76		;Assign R0 = 'L' ASCII(76)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #79		;Assign R0 = 'O' ASCII(79)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #32		;Assign R0 = ' ' ASCII(32)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #65		;Assign R0 = 'A' ASCII(65)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #75		;Assign R0 = 'K' ASCII(75)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #83		;Assign R0 = 'S' ASCII(83)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #72		;Assign R0 = 'H' ASCII(72)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #65		;Assign R0 = 'A' ASCII(65)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #89		;Assign R0 = 'Y' ASCII(89)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)
MOV R0, #33		;Assign R0 = '!' ASCII(33)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)

MOV R0, #10		;Assign R0 = '\n' ASCII(10)
SWI PrChr		;Print character to STDOUT SWI_PrChr (0x00)

LDR R0, =String	;Load String into R0
SWI PrStr		;Print String to STDOUT SWI_PrStr (0x00)