//Write an ALP to find the factorial of a number stored in R0. Save
//the value in register R1 (without using LDR and STR
//instructions).Use only registers.

MOV R0, #3
MOV R1, #1

LOOP:
    MUL R1, R0, R1
    SUBS R0, R0, #1
BNE LOOP
SWI 0x011