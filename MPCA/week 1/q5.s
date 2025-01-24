//Check if a given number is even or odd.
//Note: at the end of the program execution R2 contains 0 if
//number is even, otherwise R2 contains 1.

MOV R1, #11
ANDS R2, R1, #1
BEQ LOOP
MOV R0, #0xFF
SWI 0x011
LOOP:
    MOV R0, #0x00  