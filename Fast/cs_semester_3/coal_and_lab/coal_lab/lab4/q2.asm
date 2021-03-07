[ORG 0x0100]
jmp start
multiplicand: dq 0xABCD001112345678 ; 64 bits required
multiplier: dd 0xFFFFFFFF ; 32 bit
result: dq 0x0000000000000000 64 bits

start:
	mov cl, 32
	mov bx,1
	mov ax, [multiplicand];
	mov bx, [multiplier];

	MOV  AX, 0x4C00         ; Terminate Program 
	INT  0x21               
