        .orig x3010
        ADD     R0,      R0,      x0A
        ADD     R1,      R1,      x05
        AND     R2,      R1,      R0
        ADD     R1,      R1,      x02
        AND     R3,      R1,      R0
        TRAP    x0
	.end
