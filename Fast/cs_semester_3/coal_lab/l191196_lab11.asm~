[org 0x0100]
jmp start
tickcount: dw 0

timer:		push ax

			inc word [cs:tickcount]; increment tick count

			mov al, 0x20
			out 0x20, al ; end of interrupt

			pop ax
			iret ; return from interrupt

CRTIME:
			push ax
			push di
			push si
			
			mov ax, word[cs:tickcount]
			mov si, sp
			add sp, 2
			call word[bp+6]
			
			mov si, word[bp+4]
			sub word[cs:tickcount], ax
			push si

			pop si
			pop di
			pop ax
			mov cx, word[cs:tickcount]
ret

SUB1:
			push bp
			mov bp, sp
			push bx
	
			mov bx, word[bp+4]
			sub bx, word[bp+6]
			add bx, word[bp+4]
			sub bx, word[bp+6]

			pop bx
			pop bp
ret 4
	
;------------------------------------------------------
start:		xor ax, ax
			mov es, ax ; point es to IVT base

			cli ; disable interrupts
			mov word [es:8*4], timer; store offset at n*4
			mov [es:8*4+2], cs ; store segment at n*4+2
			sti ; enable interrupts
			
			push ax ;1st parameter of SUB1
			push bx ;2nd parameter of SUB1
			push SUB1 ;offset of sub1
			push 3 ;3 parameters follow
			call CRTIME

			mov ax, 0x4c00 ; terminate and stay redident
			int 0x21 