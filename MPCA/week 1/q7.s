//Write an ALP to find GCD of two numbers (without using LDR
//and STR instructions).Both numbers are in registers. Use only
//registers.

MOV r0, #12
MOV r1, #12

loop:
    CMP r1, r0
    BEQ L1
    BMI L2
B L3

L1:
    MOV r2, r0
    SWI 0x011

L2:
    SUB r0, r0, r1
    B loop

L3:
    SUB r1, r1, r0
    B loop