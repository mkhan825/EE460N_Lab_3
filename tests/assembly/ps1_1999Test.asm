.ORIG x3000
        AND   R3, R3, #0
        AND   R4, R4, #0
        LD    R0, NUMBERS
LOOP    LDR   R1, R0, #0
        NOT   R2, R1
        BRZ   DONE
        AND   R2, R1, #1
        BRZ   L1
        ADD   R4, R4, #1
        BRNZP NEXT
L1      ADD   R3, R3, #1
NEXT    ADD   R0, R0, #1
        BRNZP LOOP
DONE    TRAP  x25
NUMBERS .FILL x4000
        .END