[org 0x100]
	jmp start
	
printnum: push bp
mov bp, sp
push es
push ax
push bx
push cx
push dx
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov ax, [bp+4] ; load number in ax
mov bx, 10 ; use base 10 for division
mov cx, 0 ; initialize count of digits
nextdigit: mov dx, 0 ; zero upper half of dividend
div bx ; divide by 10
add dl, 0x30 ; convert digit into ascii value
push dx ; save ascii value on stack
inc cx ; increment count of values
cmp ax, 0 ; is the quotient zero
jnz nextdigit ; if no divide it again
mov di, 140 ; point di to 70th column
nextpos: pop dx ; remove a digit from the stack
mov dh, 0x07 ; use normal attribute
mov [es:di], dx ; print char on screen
add di, 2 ; move to next screen location
loop nextpos ; repeat for all digits on stack
pop di
pop dx
pop cx
pop bx
pop ax 
pop es
pop bp
	ret 2

kbisr:
	pusha
	mov ax, 0xb800
	mov es,ax
	mov ah,0
	int 0x16
	cmp ah,0x4B
	;; in al, 0x60
	;; cmp al, 0x48		;left arrow
	jne nextcmp
	
	mov byte [es:0], 'L'
	jmp nomatch
nextcmp:
	;; cmp al,0x36
	cmp ah,0x4D
	jne nomatch
	push ax
	call printnum
	mov byte [es:0],'R'
nomatch:
	mov al, 0x20		;
	mov al, 0x20	
	out 0x20,al
	popa
	iret


start:
;; 	xor ax,ax
;; 	mov es,ax
;; 	cli
;; 	mov word[es:9*4],kbisr
;; 	mov [es:9*4+2],cs
	;; 	sti
	mov bx,0000000011111111b
l1:
	;; mov ah,0
	;; int 0x16
	;; or ax,bx
	in al, 0x60
	;; cmp al, 0x48		;left arrow
	;; 	xor ax,bx
	push word ax
	call printnum

	jmp l1
	mov ax, 0x4c00
	int 21h
