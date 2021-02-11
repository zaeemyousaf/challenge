	[org 0x100]

	jmp start

printnum:
	push bp
 	mov bp, sp
 	push es
 	pusha
 	mov ah,00	
	mov al,03h	
	int 10h
 	mov ax, 0xb800
 	mov es, ax 
 	mov ax, [bp+4]
 	mov bx, 10
 	mov cx, 0 
nextdigit:

	mov dx, 0 
 	div bx 
 	add dl, 0x30
 	push dx 
 	inc cx 
 	cmp ax, 0 
 	jnz nextdigit
 	mov di, [bp+6]
nextpos: pop dx 
	mov dh, 0x07 
	mov [es:di], dx 
	add di, 2 
	loop nextpos 
	popa
	pop es
	pop bp
	ret 2

kbisr:
	pusha

	mov al,'b'
	cmp al,'a'
	jne exit
	push 123
	call printnum
exit:	
	popa
	iret

start:
	;; hook program
	mov ax,0
	mov es,ax
	cli
	mov word [es:9*4], kbisr
	mov word [es:9*4+2],cs
	sti
	;; mov ah,0
	;; int 0x16
	mov ax,0x4c00
	int 21h
	

	
