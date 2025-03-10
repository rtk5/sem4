.section .data
str:    .asciz "Hello"   @ Null-terminated string

.section .text
.global _start

_start:
    LDR R0, =str       @ Load address of the string into R0
    MOV R1, #0         @ Initialize R1 to 0 (length counter)

loop:
    LDRB R2, [R0], #1  @ Load a byte from the string into R2 and increment R0
    CMP R2, #0         @ Check if the character is null ('\0')
    BEQ done           @ If null, exit loop
    ADD R1, R1, #1     @ Increment the length counter
    B loop             @ Repeat the loop

done:
    @ Exit the program (for systems using semihosting)
    MOV R7, #1         @ syscall: exit
    SWI 0              @ Trigger the syscall
