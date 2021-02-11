[org 0x0100]
jmp start

location: dw -1
increment: dw 2

PrintChar:
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


timer:		push ax
			push bx
			push cx
			
			CheckFirstChar:
			
			cmp word[cs:location], -1
			je FirstChar
			
			mov ah, 0x7
			mov al, ' '
			push word[cs:location]
			push ax
			call PrintChar
			
			CheckTopLeft:
			cmp word[cs:location],0
			jne SkipTopLeft
			mov word[cs:increment], 2
			jmp IncrementStatement
			SkipTopLeft:
			
			CheckTopRight:
			cmp word[cs:location],158
			jne SkipTopRight
			mov word[cs:increment], 160
			jmp IncrementStatement
			SkipTopRight:
			
			CheckBottomLeft:
			cmp word[cs:location],3998
			jne SkipBottomLeft
			mov word[cs:increment], -2
			jmp IncrementStatement
			SkipBottomLeft:
			
			CheckBottomRight:
			cmp word[cs:location],3840
			jne SkipBottomRight
			mov word[cs:increment], -160
			jmp IncrementStatement
			SkipBottomRight:
			
			IncrementStatement:
			
			mov cx, word[cs:increment]
			add word[cs:location], cx
			jmp SkipFirstChar
			
			FirstChar:
			mov word[cs:location], 0
			
			SkipFirstChar:
			
			
			mov ah, 0x7
			mov al, '*'
			push word[cs:location]
			push ax
			call PrintChar
			
			

			mov al, 0x20
			out 0x20, al ; end of interrupt
			pop cx
			pop bx
			pop ax
			iret ; return from interrupt
;------------------------------------------------------
start:		xor ax, ax
			mov es, ax ; point es to IVT base

			cli ; disable interrupts
			mov word [es:8*4], timer; store offset at n*4
			mov [es:8*4+2], cs ; store segment at n*4+2
			sti ; enable interrupts

			mov dx, start ; end of resident portion
			add dx, 15 ; round up to next para
			mov cl, 4
			shr dx, cl ; number of paras

			mov ax, 0x3100 ; terminate and stay resident
			int 0x21 