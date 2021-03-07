[org 0x0100]
jmp start

a: db 0xA
b: db 0xB
c: db 0xC


FindTotal:		sub sp, 2		; for total
			push bp
			mov bp, sp
			push ax
			push bx
			push cx
			
			mov al, 0
			add al, [a]
			add al, [b]
			add al, [c]
			mov [bp+2], al

			pop cx			; restoring state
			pop bx
			pop ax
			pop bp
			pop dx
			ret
start:
	call FindTotal
	pop dx
	
	mov ax,0x4c00
	int 0x21