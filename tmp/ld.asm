        .orig x3010
        LEA     R0,      DATA1
        LDW     R1  ,    R0    ,  x0
        LDB     R2  ,    R0  ,    x0
        LDB     R3  ,    R0   ,   x1
        LDW     R4   ,   R0  ,    x0
        LDW     R4   ,   R0  ,    x1
        TRAP x0


DATA1  .FILL x1234
.end