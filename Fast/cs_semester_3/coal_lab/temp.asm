	[org 0x0100]
	jmp start
scrollup:
	;; just 1 line
	;; copy all lines and start printing from top
	;; bx points to where value to be read
	;; di points to where value to be written
	mov bx,80
	shl bx,1
	mov di,0
	mov ax,0xb800
	mov es,ax
	mov cx,0
till:
	mov dx,[es:bx]		;reading
	mov [es:di],dx		;writing
	add di,2
	add bx,2
	add cx,1
	cmp cx,1920
	jb till
	ret
start:
	
up:	
	in al,0x60
	cmp al,27
	jne up
	call scrollup
	jmp up
	mov ax, 0x4c00
	int 0x21
