[org 0x0100]
 		jmp start

prevVal:	db	0
msg1:	db 'Stop watch$'
nextLine: dw 80;
; timer displaying subroutine
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
; timer interrupt service routine
timer:
	push ax
	push ax
	mov dl, ah
GetVAl:
	in al, 0x60
	cmp dl, al
	jne setter
continue:
	mov al, 0x20
	cmp dl,	57
	je state1
	cmp dl,1
	je exittimer
	jmp display
setter:
	mov dl, al
	jmp continue
state1:
	pop ax

	;push bx;
	add word[nextLine],160;
	cmp word[nextLine],4000;
	ja resetPosition;
insideState1:
	push word[nextLine]
			mov cx, 0
	push msg1
	call SectorDis
	call delay
 	jmp display
resetPosition:
	mov word[nextLine],80
	jmp insideState1
display:
	add cx, 1
 	push cx
 	call delay
 	call printnum 
	jmp GetVAl

exittimer:
	pop ax
	pop ax
 	iret 
; display sector routine

SectorDis:
	push bp
 	mov bp, sp
 	pusha
 	mov dx, [bp+4] 
 	mov ah, 9
 	int 0x21
 	popa
 	pop bp
 	ret 2
; delay causing routine

delay:
	pusha
 	mov cx, 0x8fff
ldelay:
	sub cx, 1
 	cmp cx, 0
 	jne ldelay
 	popa
 	ret
; Starting routine
start:
	mov ah,00	
	mov al,03h	
	int 10h	
	push es 
	xor ax, ax
	mov es, ax 
	cli 
	push word [es:0x0*4]
	push word [es:0x0*4+2]
	mov word [es:0x0*4], timer
	mov [es:0x0*4+2], cs 
	sti  
	
	mov ah, 0
	int 0x16
	cmp al, 27
	je back
	
	int 0x0
	
back:
	pop word [es:0x0*4+2]
	pop word [es:0x0*4]
	pop es
	
exit:
	mov ax, 0x4c00
	int 0x21
