.ORIG x3000
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
			LEA R7, fill1
			label10		HALT
fill1		.FILL x300A
fill2		.FILL x300F
			.END