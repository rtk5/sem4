//Write an ALP using ARM7TDMI to perform to multiplication of 16X24 without using MUL instructions.(Hint: barrel shifter instructions.)
.text
mov r0, #25
mov r1, #0
add r1,r1,r0,lsl #4