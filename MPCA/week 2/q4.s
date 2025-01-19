//Write an ALP to subtract if the numbers are equal, otherwise add
//them.

.text
LDR R0, =A
LDR R1, =B
LDR R3, =C

LDR R4, [R0]
LDR R5, [R1]

CMP R4, R5
BNE LOOP

SUB R6, R4, R5
STR R6, [R3]

SWI 0x011

LOOP:
ADD R6, R4, R5
STR R6, [R3]

.data
A: .word 5
B: .word 4
C: .word 0