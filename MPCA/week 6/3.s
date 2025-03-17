.text
main:
        LDR r0, =num
        LDR r1, [r0]

        CMP r1, #1
        BEQ case_one
        CMP r1, #2
        BEQ case_two
        CMP r1, #3
        BEQ case_three
        B default_case

case_one:
        LDR r0, =msg_one
        SWI 0x02
        B end_switch

case_two:
        LDR r0, =msg_two
        SWI 0x02
        B end_switch

case_three:
        LDR r0, =msg_three
        SWI 0x02
        B end_switch

default_case:
        LDR r0, =msg_invalid
        SWI 0x02

end_switch:
        MOV r7, #1
        SWI 0

        .data
num:        .word 2
msg_one:    .asciz "One\n"
msg_two:    .asciz "Two\n"
msg_three:  .asciz "Three\n"
msg_invalid:.asciz "Invalid\n"

        .end