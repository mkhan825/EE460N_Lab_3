.ORIG X3000
        AND R0, R0, #0
        LEA R3, VAL
        LDW R3, R3, #0
        ADD R1, R3, #0

        LEA R3, NUM
        LDW R3, R3, #0
   
        ADD R2, R1, #0
LOOP    ADD R0, R0, R1
        ADD R2, R2, #-1
        BRP LOOP          
        STW R0, R3, #1
        HALT
NUM     .FILL x4000
VAL     .FILL #255
        .END