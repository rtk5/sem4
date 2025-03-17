.text

main:
    LDR r0, =x
    LDR r1, [r0]
    LDR r0, =y
    LDR r2, [r0]
    CMP r1, r2
    BGT greater_x
    B greater_y

greater_x:
    LDR r0, =msg_x
    SWI 0x02
    B end

greater_y:
    LDR r0, =msg_y
    SWI 0x02

end:
    MOV r7, #1
    SWI 0x11

.data
x: .word 10
y: .word 5
msg_x: .asciz "x is greater\n"
msg_y: .asciz "y is greater\n"










Gemini c