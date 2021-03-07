	;; lab 9 q1
[org 0x0100]
	jmp start
	
Buffer_Space: times 2000 dw 0
delay:
	push ax
	push cx
	mov cx,0
	mov ax,0
bigLoop:
	inc ax
	cmp ax,0x0FFF
	jb bigLoop
	mov ax,0
	inc cx
	cmp cx,9		;runs the loop 10 times
	jb bigLoop
	pop cx
	pop ax
	ret

clrscr:

	push es
	push cx
	push ax
	push cx
	push di
	
	mov ax, ds
	mov es, ax
	mov ax, 0xb800
	mov ds, ax
	xor si, si
	mov di, Buffer_Space
	mov cx, 2000 
	cld 
	rep movsw
	
	call delay
	call delay
	call delay
	call delay
	call delay
	call delay
	
	mov ax, es
	mov ds, ax
	
	mov ax, 0xb800
	mov es, ax 
	xor di, di 
	mov ax, 0x0720 
	mov cx, 2000 
	cld 
	rep stosw 
	
	call delay
	call delay
	call delay
	call delay
	call delay
	call delay
	
	mov ax, 0xb800
	mov es, ax 
	mov si, Buffer_Space
	xor di, di
	mov cx, 2000 
	cld 
	rep movsw
	
	pop di
	pop si
	pop ax
	pop cx
	pop es
	ret

start: call clrscr

mov ax, 0x4c00 ; terminate program
int 0x21

