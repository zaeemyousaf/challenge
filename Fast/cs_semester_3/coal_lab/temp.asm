
	[org 0x0100]
	jmp start
	
num1:	dd 0xffffEEEE
num2:	dd 0xBBBBAAAA
product: dd 0,0			;lower 4 bytes, upper 4 bites

start:
	mov ax,[sum]
	mov ax, [num1]		; ax is now : 0x00ff
	mov bx, [num2]		; ax is now : 0x00ff
	add ax,bx			;
	mov [sum],ax			;
	mov ax, [num1+2]		; ax is now : 0x00ff
	mov bx, [num2+2]		; ax is now : 0x00ff
	adc ax,bx			;
	mov [sum+2], ax			;
	mov ax, 0			;
	adc word[sum+4],ax		;

	mov ax, 0x4c00
	int 0x21
