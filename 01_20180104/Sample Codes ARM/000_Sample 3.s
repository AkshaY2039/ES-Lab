@------------------------------------------------------------------------------------------------
@ This program is an example for Updating CPSR and conditional execution.
@ syntax: MNEMONIC+CONDITION+STATUS_UPDATION <OPERANDS>
@ Remember: STATUS_UPDATION 'S' should always be the suffix of the final MNEMONIC
@ E.g. ADDSNE is not accepted because S should be a last, ADDNES is accepted
@------------------------------------------------------------------------------------------------

MOV R1, #5 			; Initialize R1 = 5
MOV R0, #3	 		; Initialize R0 = 3
ADD R1, R1, R0 		; R1 = R1 + R0
SUBS R0, R0, #1 	; R0  = R0 - 1 (update CPSR)
ADDNES R1, R1, R0	; If (prev result != 0) R1 = R1 + R0 (Update CPSR)
SUBS R0, R0, #1		; R0  = R0 - 1 (update CPSR)
ADDNES R1, R1, R0	; If (prev result != 0) R1 = R1 + R0 (Update CPSR)
SUBS R0, R0, #1		; R0  = R0 - 1 (update CPSR)
ADDNES R1, R1, R0	; If (prev result != 0) R1 = R1 + R0 (Update CPSR)