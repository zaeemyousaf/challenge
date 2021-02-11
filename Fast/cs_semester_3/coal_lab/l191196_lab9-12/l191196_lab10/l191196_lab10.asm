	;; lab 10
	;; Asterick travels and isr gives the control back
	;; at any time, you can exit
[org 0x0100]
	jmp start

init_loc: dw -1

draw_char:
	push bp
	mov bp, sp
	push es
	push ax
	push bx
	push cx
	push dx
	push di
	
	mov ax, 0xb800
	mov es, ax
	mov ax, [bp+4]
	mov di, [bp+6]
	
	mov [es:di], ax
	
	pop di
	pop dx
	pop cx
	pop bx
	pop ax 
	pop es
	pop bp

	ret 4


tmisr:
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	

	cmp word[cs:init_loc], -1
	je empty_char
	
	mov ah, 0x17
	mov al, 0x20
	push word[cs:init_loc]
	push ax
	call draw_char
	
move_left:

	cmp word[cs:init_loc],0
	jne skip_left
	mov word[cs:2], 2
	jmp next_pos

skip_left:
	
top_right_test:
	cmp word[cs:init_loc],158
	
	jne skip_top_right
	mov word[cs:2], 160
	jmp next_pos	
skip_top_right:
	
bottom_test:
	cmp word[cs:init_loc],3998
	jne skip_bot_test
	mov word[cs:2], -2
	jmp next_pos
skip_bot_test:
	
bottom_cor_test:
	cmp word[cs:init_loc],3840
	jne skip_bot_cor
	mov word[cs:2], -160
	jmp next_pos
skip_bot_cor:
	
next_pos:
	
	mov cx, word[cs:2]
	add word[cs:init_loc], cx
	jmp skip_empty
	
empty_char:
	mov word[cs:init_loc], 0
	
skip_empty:
	
	mov ah, 0x17		;
	mov al, 42		;asterick symbol
	push word[cs:init_loc]
	push ax
	call draw_char
	
	
	
	mov al, 0x20
	out 0x20, al ; send eof to pic
	
	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	iret ; return from int


hook_tmisr:
	push ax
	push bx
	push es
	
	xor ax, ax
	mov es, ax 
	
	cli 
	mov word [es:8*4], tmisr
	mov [es:8*4+2], cs 
	sti

	pop es
	pop bx
	pop ax
	ret

start:
 	call hook_tmisr
	
	mov dx, start 
	add dx, 15 ; round up to next para
	mov cl, 4
	shr dx, cl ; number of paras
	
	mov ax, 0x3100 ; terminate and stay resident
	int 0x21 
