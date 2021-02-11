[org 0x0100]
jmp start

oldisr: dd 0 

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
			jne compare2 
			
			mov ax, cs
			mov ds, ax
			
			mov ax, ds
			mov es, ax
			mov ax, 0xb800
			mov ds, ax
			xor si, si
			mov di, Buffer
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
			
compare2:	cmp al, 10011110b
			jne nomatch
			
			call sleep
			call sleep
			
			mov ax, cs
			mov ds, ax
			
			mov ax, 0xb800
			mov es, ax 
			mov si, Buffer
			xor di, di
			mov cx, 2000 
			cld 
			rep movsw
			
			jmp exit
		
nomatch:	pop ds
			pop si
			pop di	
			pop cx
			pop ax
			pop es
			jmp far[cs:oldisr] ; call the original ISR

exit:		mov al, 0x20
			out 0x20, al ; send EOI to PIC
			pop ds
			pop si
			pop di	
			pop cx
			pop ax
			pop es
			iret ; return from interrupt

;-------------------------------------------------------------------
start:	xor ax, ax
		mov es, ax 
		mov ax, [es:9*4]
		mov [oldisr], ax 
		mov ax, [es:9*4+2]
		mov [oldisr+2], ax 

		cli 
		mov word [es:9*4], kbisr 
		mov [es:9*4+2], cs 
		sti

		mov dx, start 
		add dx, 15 
		mov cl, 4
		shr dx, cl 
		
		mov ax, 0x3100 
		int 0x21 
		
Buffer: times 2000 dw 0