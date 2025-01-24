//1.Write an ALP using ARM7TDMI to find whether the given number is even parity.

.TEXT
        LDR R0, =6             
        MOV R1, #0             
        MOV R2, #8             

Loop:
        AND R3, R0, #1         @ Extract the least significant bit (LSB) of R0
        ADD R1, R1, R3         @ Add the LSB to the counter R1
        MOV R0, R0, LSR #1     @ Logical shift R0 right by 1 bit
        SUB R2, R2, #1         @ Decrement the loop counter R2
        CMP R2, #0             @ Compare R2 with 0
        BNE Loop               @ Repeat the loop if R2 is not 0

        AND R3, R1, #1         @ Check if the count of 1s is even (R1 AND 1)
        CMP R3, #0             @ Compare R3 with 0
        BEQ EvenParity         @ If zero, the parity is even
        B OddParity            @ Otherwise, the parity is odd

EvenParity:
        MOV R4, #1             @ Set R4 to 1 to indicate even parity
        B End

OddParity:
        MOV R4, #0             @ Set R4 to 0 to indicate odd parity

End:
        SWI 0x011              @ End of the program