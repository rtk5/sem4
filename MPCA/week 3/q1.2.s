//Write an ALP using ARM7TDMI to perform to multiplication of 16X24 without using MUL instructions.(Hint: barrel shifter instructions.)
.text
mov r0, #16
add r0,r0,r0,lsl #2
add r0,r0,r0,lsl #2

