.ORIG x3000
AND R0, R0, #0
ADD R1, R1, #1
ADD R2, R2, #2
ADD R3, R3, #3
ADD R4, R4, #4
ADD R5, R5, #5
ADD R6, R6, #6
ADD R7, R7, #7
AND R6, R6, #0
NOT R6, R6
LSHF R6, R6, #12
ADD R6, R6, R7
ADD R6, R6, #15
ADD R6, R6, #15
LEA R5, A
LOOP  AND R1, R1, #0
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
ADD R1, R1, #1
A  STW R6, R5, #-32
BR LOOP
HALT
.END
