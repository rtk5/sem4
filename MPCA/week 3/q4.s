.text
ldr r9, = A
mov r1,#3
mov r2,#3
mov r3,#2
mov r4,#2
mla r5,r2,r3,r4
mov r6,r5,lsl #2
add r9,r9,r6

.data
A: .word 1,2,3,4,5,6,7,8,9
