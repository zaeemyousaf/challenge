
[org 0x0100]
	jmp start
	
str1:	db 'I am learning assembly',0 ; null terminated string
	;; ax after should have 0x16 (22 decimal) value

strLength:
	push bp
	mov bp,sp
	;; stack[length,str,call,bp,ax,cx,di,
	push ax
	push cx
	push di
	push ds
	pop es

	mov di,[bp+4]		; pointing to string
	mov cx,0xFFFF		; assuming very large string
	mov al,0
	repne scasb
	mov ax,0xFFFF
	sub ax,cx
	dec ax
	mov [bp+6],ax		; store length
	;; restore local variables
	pop di
	pop cx
	pop ax
	pop bp
	ret 2
	
	
start:
	push 0			; length of string
	mov ax,str1		;
	push ax
	call strLength
	pop ax
	
	mov ax, 0x4c00
	int 0x21
