//3. Write an ALP to perform not operation using only mov and
//bitwise logical operation.

MOV R2, #5
MOV R1, #0XFFFFFFFF
BIC R0, R1, R2
SWI 0X011