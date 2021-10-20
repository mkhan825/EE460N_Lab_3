        .orig x4000

START  LEA R0, DATA
        ADD R0, R0, R0
        TRAP x0

DATA   .fill x1234                  ;0x4006
.end
