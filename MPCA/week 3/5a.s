.text
ldr r0, =A
ldr r1, =B
mov r8,#0
mov r5,#3

loop:
    ldr r2, [r0], #4
    ldr r3, [r1], #4
    mul r4,r2,r3
    add r8,r4,r8
    subs r5,r5,#1
    beq end_program
    b loop

end_program:
    swi 0x011

.data
A: .word 1,2,3
B: .word 4,5,6