        .orig x3400

        ;; 1) test unconditional branch.
START  BR LBR                  ;0x3400
        BR DONE

        ;; 3) test branch zero.
LBRp   XOR R1, R1, R1
        BRp DONE
        BRn DONE
        BRz LBRz

        ;; 6.1) test branch np.
LBRnz2 ADD R3, R3, #-6
        BRz DONE
        BRnp LBRnp1             ;0x3410
        
        ;; 2) test branch positive.
LBR    ADD R0, R0, x1
        BRn DONE
        BRz DONE
        BRnz DONE
        BRp LBRp

        ;; 5.2) test branch nz.
LBRnz1 XOR R2, R2, R2
        BRp DONE
        BRnz LBRnz2             ;0x3420

        ;; done
LBRzp2 ADD R6, R6, xb
        BRnzp DONE
        
        ;; 6.2) test branch np.
LBRnp1 ADD R4, R4, xa
        BRz DONE
        BRnp LBRnp2
        
        ;; 5.1) test branch nz.
LBRn   ADD R2, R2, #-1
        BRp DONE
        BRnz LBRnz1             ;0x3430

        ;; 7.2) test branch zp
LBRzp1 ADD R3, R4, #-1
        BRn DONE
        BRzp LBRzp2
        
        ;; 4) test branch negative.
LBRz   ADD R1, R1, #-1          ; R1 should be -1.
        BRp DONE
        BRz DONE
        BRn LBRn

        ;; 7.1) test branch zp
LBRnp2 AND R5, R5, x0           ;0x3440
        BRn DONE
        BRzp LBRzp1
        
DONE   TRAP x0
.end