.ORIG x3000
DOIT     STW   R1, R6, #0
         ADD   R6, R6, #2
         AND   R3, R1, R2
         BRz   EVEN
         ADD   R1, R1, #3
         ADD   R5, R5, #-1
         BRp   DOIT
EVEN     ADD   R1, R1, #1
         ADD   R7, R7, #-1 
         BRp   DOIT
.END