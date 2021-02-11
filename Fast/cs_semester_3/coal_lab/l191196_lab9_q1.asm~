[org 0x0100]
jmp start

sleep: 
push cx
mov cx, 0xFFFF

	delay: loop delay
	mov cx, 0xFFFF

	delay1: loop delay1
	mov cx, 0xFFFF

	delay2: loop delay2
	mov cx, 0xFFFF

pop cx
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
	mov di, Buffer
	mov cx, 2000 
	cld 
	rep movsw
	
	call sleep
	call sleep
	call sleep
	call sleep
	call sleep
	call sleep
	
	mov ax, es
	mov ds, ax
	
	mov ax, 0xb800
	mov es, ax 
	xor di, di 
	mov ax, 0x0720 
	mov cx, 2000 
	cld 
	rep stosw 
	
	call sleep
	call sleep
	call sleep
	call sleep
	call sleep
	call sleep
	
	mov ax, 0xb800
	mov es, ax 
	mov si, Buffer
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

Buffer: times 2000 dw 0