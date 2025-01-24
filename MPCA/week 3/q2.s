//2. Write an ALP using ARM7TDMI to add only even numbers stored in memory location for a given set of numbers and store the sum in the memory location.

.text
ldr r0, =array
ldr r3, =evensum
mov r4, #0
mov r5, #10

loop:
    ldr r1, [r0]
    ands r2, r1, #1
    beq even
    add r0, r0, #4
    subs r5, r5, #1
    bne loop
    b end

even:
    add r4, r4, r1
    add r0, r0, #4
    subs r5, r5, #1
    bne loop

end:
    str r4, [r3]
    swi 0x011

.data
array: .word 15, 10, 12, 13, 9, 45, 16, 8, 25, 33
evensum: .word 0
