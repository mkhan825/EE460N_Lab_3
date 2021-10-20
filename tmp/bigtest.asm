			.ORIG x3000
			ADD R0, R0, #1 		;00
			ADD R1, R1, #-1 	;02
			ADD R2, R2, #2		;04
			ADD R3, R3, #-3		;06
			ADD R4, R4, #4		;08
			ADD R5, R5, #-5		;A
			ADD R6, R6, #6		;C
			ADD R7, R7, #-7		;E
			ADD R7, R7, R7		;10
			AND R0, R0, R7		;12
			AND R2, R4, #12	;	 14        R2 <- 4 + 12
			BRn label1		;16
			ADD R6, R6, #1		;18
label1		BRz label2			;1A
			ADD R6, R6, #1		;1C
label2		BRp label3			;1E
			ADD R6, R6, #1		;20
label3		BRnz label4			;22
			ADD R6, R6, #1		;24
label4		BRnp label5			;26
			ADD R6, R6, #1		;28
label5		BRnzp label6			;2A
			ADD R6, R6, #1		;2C
label6		ADD R6, R6, #4			;2E
			JSR label7		;30		
			AND R2, R2, #0		;32
			BRz label8	;THIS ONE 34
			ADD R6, R6, #3		;36
label7		ADD R6, R6, #2			;38
			RET			;3A
label8      JSR label9				;3C
			ADD R6, R6, #2		;3E
label9      AND R2, R2, #0			;40
			ADD R6, R6, #1		;42
    		LEA R2, fill1			;44----------------------------------------------------------------------- Problem down
			LDW R2, R2, #0		;46 
			LDB R2, R2, #3		;48
			ADD R6, R6, R2
			LEA R2, fill2
			LDW R2, R2, #0
			LDW R2, R2, #0
			ADD R5, R5, R2
			NOT R5, R6
			LSHF R3, R6, #2
			RSHFL R1, R5, #2
			RSHFA R2, R5, #2
			LEA R7, fill1 ;------------------------------------------------------------------------------- half chunk
			STB R2, R7, #0
			STB R3, R7, #1
			STW R6, R7, #1
			XOR R1, R6, R3
			XOR R1, R6, xF
			LEA R2, label11
			JMP R2
			ADD R6, R6, #2
label11 	LEA R2, label10
            JSRR R2
		    ADD R6, R6, #10
label10		HALT
fill1		.FILL x300A
fill2		.FILL x300F
			.END