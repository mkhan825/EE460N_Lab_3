        .orig x5000

        LEA ,    R0  ,    ADDR
        LDW  ,   R0  ,    R0   ,   x0
        ADD   ,  R1,      R1   ,   x003
        STW  ,   R1   ,   R0   ,   x0
        LDW  ,   R2  ,    R0   ,   x0
        TRAP    x0

ADDR   .fill x5100
.end