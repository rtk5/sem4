.text

_start:
    ldr r0, =Dividend
    ldr r1, =Divisor
    ldr r2, [r0]
    ldr r3, [r1]

subtract_loop:
    subs r4, r2, r3
    blt end_program
    mov r2, r4
    b subtract_loop

end_program:
    add r4, r2, r3
    ldr r5, =Remainder
    str r4, [r5]
    swi 0x11

.data
Dividend: .word 10
Divisor: .word 3
Remainder: .word 0