MOV R1, #5 			; Initialize R1 = 5
MOV R0, #3	 		; Initialize R0 = 3
ADD R1, R1, R0 		; R1 = R1 + R0
SUBS R0, R0, #1 	; R0  = R0 - 1 (update CPSR)
ADDNES R1, R1, R0	; If (prev result != 0) R1 = R1 + R0 (Update CPSR)
SUBS R0, R0, #1		; R0  = R0 - 1 (update CPSR)
ADDNES R1, R1, R0	; If (prev result != 0) R1 = R1 + R0 (Update CPSR)
SUBS R0, R0, #1		; R0  = R0 - 1 (update CPSR)
ADDNES R1, R1, R0	; If (prev result != 0) R1 = R1 + R0 (Update CPSR)