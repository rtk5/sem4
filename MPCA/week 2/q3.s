//3. Write a ALP using ARMTDMI-ISA to store odd and even numbers in separate memory locations starting from LOCA and LOCB respectively

.text
ldr r0, =ARRAY
ldr r1, =LOCA
ldr r2, =LOCB
mov r3, #10

loop:
    ldr r4, [r0], #4
    ands r5, r4, #1
    beq store_even
    str r4, [r2], #4
    subs r3, r3, #1
    bne loop
    b end

store_even:
    str r4, [r1], #4
    subs r3, r3, #1
    bne loop

end:
    swi 0x011

.data
ARRAY: .word 10, 50, 41, 55, 30, 20, 11, 5, 100, 77
LOCA: .word 0, 0, 0, 0, 0
LOCB: .word 0, 0, 0, 0, 0
