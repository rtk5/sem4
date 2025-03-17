.text
        MOV R1, #5      
        MOV R2, #3        

        AND R3, R1, R2    
        ORR R4, R1, R2    
        EOR R5, R1, R2   

        MOV R0, #1        
        LDR R7, =msg_and
        SWI 0

        MOV R0, #1
        LDR R7, =msg_or
        SWI 0

        MOV R0, #1
        LDR R7, =msg_xor
        SWI 0

        MOV R7, #1
        SWI 0

        .data
msg_and:  .asciz "AND: %d\n"
msg_or:   .asciz "OR: %d\n"
msg_xor:  .asciz "XOR: %d\n"