.global _start

.section .data
    A:      .word 1, 2, 3, 4, 5, 6, 7, 8, 9
    B:      .word 1, 1, 2, 2, 3, 3, 4, 4, 5
    C:      .word 0, 0, 0, 0, 0, 0, 0, 0, 0
    N:      .word 3

.section .text
_start:
    LDR R10, =A
    LDR R11, =B
    LDR R12, =C
    LDR R5, =N
    LDR R5, [R5]

    MOV R0, #0
row_loop:
    CMP R0, R5
    BGE end_program

    MOV R1, #0
col_loop:
    CMP R1, R5
    BGE next_row

    MOV R9, #0
    MOV R2, #0
mul_loop:
    CMP R2, R5
    BGE store_C

    MUL R3, R0, R5
    ADD R3, R3, R2
    LDR R6, [R10, R3, LSL #2]

    MUL R4, R2, R5
    ADD R4, R4, R1
    LDR R7, [R11, R4, LSL #2]

    MUL R8, R6, R7
    ADD R9, R9, R8

    ADD R2, R2, #1
    B mul_loop

store_C:
    MUL R3, R0, R5
    ADD R3, R3, R1
    STR R9, [R12, R3, LSL #2]

    ADD R1, R1, #1
    B col_loop

next_row:
    ADD R0, R0, #1
    B row_loop

end_program:
    MOV R7, #1
    SWI 0
