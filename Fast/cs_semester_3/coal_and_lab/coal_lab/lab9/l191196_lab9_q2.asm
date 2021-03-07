[org 0x0100]
	jmp start
Buffer_Space: times 2000 dw 0
	
oldisr: dd 0 

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

kbisr:		
	push es
	push ax
	push cx
	push di
	push si
	push ds
	
	mov ax, 0xb800
	mov es, ax ; point es to video memory
	
	mov ax, 0
	in al, 0x60 ; read a char from keyboard port
	
	cmp al, 30 
	jne next_cmp 
	
	mov ax, cs
	mov ds, ax
	
	mov ax, ds
	mov es, ax
	mov ax, 0xb800
	mov ds, ax
	xor si, si
	mov di, Buffer_Space
	mov cx, 2000 
	cld 
	rep movsw
	
	mov ax, es
	mov ds, ax
	
	mov ax, 0xb800
	mov es, ax 
	xor di, di 
	mov ax, 0x0720 
	mov cx, 2000 
	cld 
	rep stosw 
	
	jmp exit
			
next_cmp:

	cmp al,158
	jne nomatch
	
	call delay
	
	mov ax, cs
	mov ds, ax	
	mov ax, 0xb800
	mov es, ax 
	mov si, Buffer_Space
	xor di, di
	mov cx, 2000 
	cld 
	rep movsw
	
	jmp exit
		
nomatch:
	pop ds
	pop si
	pop di	
	pop cx
	pop ax
	pop es
	jmp far[cs:oldisr] ; load original ISR

exit:
	mov al, 0x20
	out 0x20, al ; send EOI to PIC
	pop ds
	pop si
	pop di	
	pop cx
	pop ax
	pop es
	iret ; return from interrupt

;;;-----------------------------
store_old_isr:
	push ax
	push bx
	push es
	
	xor ax, ax
	mov es, ax 
	mov ax, [es:9*4]
	mov [oldisr], ax 
	mov ax, [es:9*4+2]
	mov [oldisr+2], ax

	pop es
	pop bx
	pop ax
	ret

hook_kbisr:
	push ax
	push bx
	push es
	
	xor ax, ax
	mov es, ax 
	
	cli 
	mov word [es:9*4], kbisr 
	mov [es:9*4+2], cs 
	sti

	pop es
	pop bx
	pop ax
	ret

start:
	call store_old_isr
	call hook_kbisr

	mov dx, start 
	add dx, 15 		;next round
	mov cl, 4
	shr dx, cl 
		
	mov ax, 0x3100 	;stay resident
	int 0x21 
		
