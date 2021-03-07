	;; lab 12
	;; It was difficult but thought provoking
	;; it is buggy 
[org 0x100]

	jmp start
alloc_msg:	db 'allocating ',0
	
clearScreen:
	push bp
	mov bp,sp
	push ax
	push es
	push di
	push cx

	mov ax, 0xb800
	mov es,ax
	mov di,0
	mov ah,0x00
	mov al,0x20
	mov cx,2000
	rep stosw
	;; screen has been cleared
	pop cx
	pop di
	pop es
	pop ax
	pop bp
	ret

printnum:
	push bp
	mov bp,sp
	push es
	push ax
	push bx
	push cx
	push dx
	push di

	mov ax,0xb800
	mov es,ax
	mov ax,[bp+4]
	mov bx,10
	mov cx,0
nextdigit:
	mov dx,0
	div bx
	add dl,0x30
	push dx
	inc cx
	cmp ax,0
	jnz nextdigit

	;; compute location
	push ax
	push bx
	
	mov ax,[bp+6]		;xy
	shl ax,8		; y is in lower byte (discarding higer part)
	shr ax,8		; higer part discarded
	mov bh,80
	mul bh			;80*y
	mov bx,[bp+6]		;xy
	shr bx,8			;x is in upper byte
	add ax,bx		;(80*y)+x
	shl ax,1			;2(80*y+x) actual position
	
	mov di,ax
	pop bx
	pop ax

nextpos:
	pop dx
	mov dh,0x07
	mov [es:di],dx
	add di,2
	loop nextpos

	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	pop es
	pop bp
	ret 4

printstr:
	;; this code taken from book is not commented pg. 113
	push bp
	mov bp,sp
	push es
	push ax
	push cx
	push si
	push di

	push ds
	pop es
	mov di, [bp+4]
	mov cx,0xffff
	xor al,al
	repne scasb
	mov ax, 0xffff
	sub ax,cx
	dec ax
	jz exit

	mov cx,ax
	mov ax,0xb800
	mov es,ax
	mov al,80
	mul byte [bp+8]
	add ax,[bp+10]
	shl ax,1
	mov di,ax
	mov si,[bp+4]
	mov ah,[bp+6]

	cld
nextchar:
	lodsb
	stosw
	loop nextchar
exit:
	pop di
	pop si
	pop cx
	pop ax
	pop es
	pop bp
	ret 8

InitializeRecordKeeping:
	push bp
	mov bp, sp
	
	push ax
	push bx
	push cx
	push dx
	push di

	
	mov cx, 0
	mov di, word[bp+4]
	mov cx, word[bp+6]
	
	sub cx, 2
	mov byte[di], cl
	inc di
	
while_lt_zero:
	mov byte[di], '@'
	inc di
	dec cx
	jnz while_lt_zero
	
	mov cx, word[bp+6]
	mov byte[di], cl
	
	pop cx
	pop di
	pop bp
	ret 4	
	
AllocateBlock:
	push bp
	mov bp, sp
	push cx
	push di
	push si
	push ax
	
	mov cx, word[bp+4]
	mov di, EndOfProgram
	
	mov ax, cx
	add ax, 2
	
	cmp byte[di], cl
	jge skip_glitch
	
glitch:
	
	mov word[bp+6], 0xFFFF
jmp _exit
	
skip_glitch:
	
	
	
	
	mov ax, word[di]
	add di, ax
	inc di
	
	mov byte[di], 0
	sub di, cx
	sub di, 1
	mov byte[di], cl
	
	dec di
	sub byte[di], cl
	sub byte[di], 2
	mov si, di
	
	mov di, EndOfProgram
	sub byte[di], cl
	sub byte[di], 2
	
	inc si
	mov word[bp+6], si
	
_exit:
	pop di
	pop dx
	pop cx
	pop bx
	pop ax

	pop bp
	ret 2

start:
	call clearScreen
	push 0x28
	push 0x01
	push 0x02
	xor ax,ax
	mov ax,alloc_msg	
	push ax
	call printstr

	push 0x3501
	push 0x02
	call printnum
	
	mov ax, 0
	mov al, 20		; allocating 20 bytes
	push ax
	push EndOfProgram
	call InitializeRecordKeeping
	
	
	push 0x0
	push 0x0003		; utilize three bytes
	call AllocateBlock
	pop ax

	push 0x3
	push 0x0007		; utilize 7 bytes
	call AllocateBlock	
	pop ax

	push 0x7
	push 0x0002		; utilize 2 bytes at 7th index
	call AllocateBlock
	pop ax

	mov ax, 0x4c00
	int 0x21

EndOfProgram: dw 0
