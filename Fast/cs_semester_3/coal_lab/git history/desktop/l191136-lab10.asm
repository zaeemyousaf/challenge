[org 0x100]

	jmp start

;---------------------------------------
Frame:
	push bp
	mov bp, sp
	push ax
	push bx 
	push cx
	push di
	push es

	mov ah,00	
	mov al,03h	; interrupt to clear screen
	int 10h		
	
	mov ah, 0x07
	mov al, '+'
	
	mov bx, 0xb800
	mov es, bx
	mov di, [bp+4]
	mov cx, 0
	add cx, 3	

l1:	mov [es:di], ax
	add di, 2
	sub cx, 1
	cmp cx, 0
	jne l1
	mov [es:di], ax
	add cx, 3
l2:	add di, 160
	mov [es:di], ax
	sub cx, 1
	cmp cx, 0
	jne l2
	mov [es:di], ax
	add cx, 3
l3:	sub di, 2
	mov [es:di], ax
	sub cx, 1
	cmp cx, 0
	jne l3
	mov [es:di], ax
	add cx, 3
l4:	sub di, 160
	mov [es:di], ax
	sub cx, 1
	cmp cx, 0
	jne l4

	pop es
	pop di
	pop cx
	pop bx
	pop ax
	pop bp
	ret
;---------------------------------------	
start:	
	push 350	
	call Frame
		
input:	mov ah, 0
	int 0x16 
	cmp al, 'u'
	je GoUp
	cmp al, 'd'
	je GoDown
	cmp al, 'L'
	je GoLeft
	cmp al, 'R'
	je GoRight
	cmp al, 27
	je end
	jmp input	

GoUp:	pop ax
	sub ax, 160
	push ax	
	call Frame
	jmp input

GoDown:	pop ax
	add ax, 160
	push ax	
	call Frame
	jmp input

GoLeft:	pop ax
	sub ax, 2
	push ax	
	call Frame
	jmp input

GoRight:pop ax
	add ax, 2
	push ax	
	call Frame
	jmp input

end:	pop ax
	mov ax, 0x4c00
	int 21h
