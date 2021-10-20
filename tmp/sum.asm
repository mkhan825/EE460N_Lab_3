        .orig x3000

START  LEA     R0  ,    INPUT
        LDW     R0  ,    R0    ,  x0 ; R0 will contain the factorial

        ADD     R1 ,     R0   ,   x0 ; R1 will be decremented at each iteration

LOOP   ADD     R1    ,  R1  ,    #-1
        BRnz    DONE
        ADD     R0     , R1   ,   R0
        BR      LOOP

DONE   TRAP x0
        
        
INPUT  .fill #8                     ; compute 8 + 7 + .. + 1
.end