.text
main:
        LDR r0, =a
        LDR r1, [r0]
        LDR r0, =b
        LDR r2, [r0]
        LDR r9, =result

        BL add
        LDR r8, =msg_sum
        SWI 0x02

        STR r0, [r9]
        SWI 0x02
    
        MOV r7, #1
        SWI 0x11

add:
        ADD r0, r1, r2
        BX lr

        .data
a:      .word 5
b:      .word 3
result: .word 0
msg_sum: .asciz "Sum: \n"

        .end