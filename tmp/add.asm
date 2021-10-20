.ORIG x3000
LEA R0, addr1
LDW R0, R0, #0
LDW R1, R0, #0
AND R2, R2, #0
ADD R2, R2, #1
STW R2, R1, #0

;Calculate the sum
LEA R0, addr2
LDW R0, R0, #0 ;Pointer to beginning array
AND R4, R4, #0
ADD R4, R4, #10
LOOP LDB R1, R0, #0 ;Value
LDB R2, R0, #1 ;2nd value
ADD R3, R1, R2 ;R3 has sum
ADD R0, R0, #2
ADD R4, R4, #-1 ;R4 Counter
BRP LOOP
LEA R0, addr3
LDW R0, R0, #0
STB R3, R0, #0
HALT
addr1 .FILL x4000
addr2 .FILL xC000
addr3 .FILL xC014
.END