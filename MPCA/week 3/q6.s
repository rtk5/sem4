//2. Write an ALP using ARM7TDMI  to multiplication of 38X72  without using MUL instructions.

.text
mov r0,#38
add r0,r0,r0,lsl #3
mov r0,r0,lsl #3