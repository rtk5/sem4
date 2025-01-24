//Write an ALP to perform Addition of two numbers of size
//a) 64 bit b) 128 bit
//Save the result in register (reuse the register to store the result)


MOV R0, #0XFFFFFFFF
MOV R1, #0XFFFFFFFF
MOV R2, #0XFFFFFFFF
MOV R3, #0XFFFFFFFF
ADD R0, R0, R2
ADCS R1, R1, R3