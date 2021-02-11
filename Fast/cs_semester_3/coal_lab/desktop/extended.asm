	;;  extended addition
	[org 0x0100]
	JMP start
num1: dd 0xEFFF00F2
num2: dd 0xEEEE2324
num3: dd 0x0			;0xDDED2416 (16 24 ED DD)

start:
	mov ax, [num1]		; F2 00 FF EE
	mov bx, [num2]		; 24 23 EE EE
	add ax, bx		;6152
	
	mov [num3], ax		;
	jc add1
	add ax, 1
	mov ax, [num1+2]	;
	mov bx, [num2+2]		; 24 23 EE EE
	
addition:
	add ax, bx		;
	mov [num3+2], ax	;

	mov ax, 0x4c00
	int 0x21
