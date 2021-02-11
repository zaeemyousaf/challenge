	[org 0x0100]
	jmp start
	
a:	dw 10
b:	dw 20

sum:
	add ax,bx
	ret

dec:
	push ax
	mov ax, [sp+4]
	sub ax,1
	
	ret
start:
	push [a]
	mov ax,[sp+2]
	
	;; mov ax,[a]
	;; mov bx,[b]
	;; push ax
	;; call dec
	;; push bx
	;; call dec
	;; push ax
	;; push bx
	;; call sum

	mov ax,0x4c00
	int 0x21

	
	
