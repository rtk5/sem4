.text
ldr r9, =A
ldr r10, =B
mov r11,#8

loop:
    ldmia r9!, {r0-r3}
    stmia r10!,{r0-r3}
    sub r11,r11,#1
    cmp r11,#0
    beq end_program
    b loop

end_program:
    swi 0x011


.data
A: .word 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
B: .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0