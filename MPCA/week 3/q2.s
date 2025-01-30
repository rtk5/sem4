.data
A:  .word 1, 2, 3, 4, 5, 6, 7, 8, 9

.text
LDR R0, =A          @ Load the base address of array A into R0
LDR R1, [R0]        @ Load the first element of array A into R1
MOV R2, #7          @ Set R2 to the target value 7
MOV R3, #9          @ Set R3 to the maximum loop count (size of array)
MOV R4, #1          @ Initialize R4 as the loop counter

LOOP:
    CMP R1, R2       @ Compare current element with 7
    BEQ LOOP2        @ If equal, branch to LOOP2
    CMP R3, R4       @ Check if the loop counter has reached 9
    BEQ LOOP3        @ If so, branch to LOOP3
    ADDS R4, R4, #1  @ Increment the loop counter
    LDR R1, [R0], #4 @ Load the next element and increment the pointer
    BNE LOOP         @ Repeat the loop if not finished

    MOV R2, #0       @ Default result if the loop completes without a match
    SWI 0x011        @ Terminate the program

LOOP2:
    MOV R2, #1       @ Set result to 1 if 7 is found
    SWI 0x011        @ Terminate the program

LOOP3:
    MOV R2, #0       @ Set result to 0 if loop counter reaches 9 without finding 7
    SWI 0x011        @ Terminate the program
