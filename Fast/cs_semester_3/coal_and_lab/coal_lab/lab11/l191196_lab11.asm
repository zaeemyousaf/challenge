	;; lab 11 Q1
[org 0x0100]
	jmp start

timerTick: dw 0

tmisr:
	push ax
	
	inc word [cs:timerTick]; increment tick count
	
	mov al, 0x20
	out 0x20, al ; end of interrupt
	
	pop ax
	iret ; return from interrupt
	
CRTIME:	
	push ax
	push bx
	push cx
	push dx
	push di
	push si
	
	mov si, sp
	add sp, 2
	call word[bp+6]
	mov ax, word[cs:timerTick]

	mov si, word[bp+4]
	sub word[cs:timerTick], ax
	push si
	;; populate the registers 
	pop si
	pop di
	pop dx
	pop cx
	pop bx
	pop ax

	mov cx, word[cs:timerTick] ;read timerTick in cx
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
	
	push ax ;1st para 
	push bx ;2nd para 
	push SUB1 ;offset of sub1
	push 3	  ;total three parameters
	call CRTIME
	;; all pushed will be cleared by callee
	
	mov ax, 0x4c00 ; terminate and stay redident
	int 0x21 
