//4. Write an ALP using ARM7TDMI to find the largest number from a given set of numbers:

.text
ldr r0, =A          
ldr r1, [r0]        
mov r2, #9          
add r0, r0, #4      

loop:
    ldr r3, [r0]    
    cmp r3, r1      
    ble skip         
    mov r1, r3       
skip:
    add r0, r0, #4   
    subs r2, r2, #1 
    bne loop         

ldr r4, =RESULT     
str r1, [r4]        
swi 0x011           

.data
A:      .word 10, 50, 41, 55, 30, 20, 11, 5, 100, 77
RESULT: .word 0
