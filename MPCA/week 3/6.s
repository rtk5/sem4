.text
    .global _start

_start:
    LDR R0, =0x788
    MOV R1, #0

SUM_LOOP:
    AND R2, R0, #0xF
    ADD R1, R1, R2
    MOV R0, R0, LSR #4
    CMP R0, #0
    BNE SUM_LOOP

    B .

    .end