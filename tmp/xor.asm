        .orig x3400

        ;; Load R0 with 0xAAAA
        ADD     R0 ,     R0  ,    xA
        LSHF    R0   ,   R0   ,   #4
        ADD     R0   ,   R0   ,   xA
        LSHF    R0   ,   R0   ,   #4
        ADD     R0   ,   R0   ,   xA
        LSHF    R0   ,   R0   ,   #4
        ADD     R0   ,   R0   ,   xA

        NOT     R1  ,    R0

        XOR     R2    ,  R1 ,     #-1

        TRAP    x25
.end