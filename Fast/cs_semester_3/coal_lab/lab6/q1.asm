	[org 0x0100]
	jmp start
power:
	push bp
	mov bp,sp		;[0,base,power,call,bp,ax,cx]
	push ax
	push cx

	mov cx,[bp+4]
	mov ax,1

while:
	cmp cx,0
	jbe endWhile
	mul word [bp+6]
	dec cx
	jmp while
	
endWhile:	
	mov [bp+8],ax
	;; restore values
	pop cx
	pop ax
	pop bp
	ret 4
start:
	push 0			; result is saved here
	push 2
	push 4
	call power
	pop ax
	
	mov ax,0x4c00
	int 0x21
