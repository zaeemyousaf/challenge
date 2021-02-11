
	[org 0x0100]
	jmp start	
	;; pass three parameters to compute their sum in dx
	;; call function three times
findSum:
	push bp
	push ax
	;; 	[10,20,30,call_next,pb,ax]
	mov bp,sp		;sp and bp points to cx
	mov ax,0		; ax is initialized to zero
	add ax,[bp+6]		;30
	add ax,[bp+8]		;20
	add ax,[bp+10]		;10
	mov dx,ax		; 3D

	;; restore values of pb and ax
	pop ax
	pop bp
	ret
	
start:
	push 10			; first number
	push 20			; second number
	push 30			; third number (sum is 3C)

	call findSum		; first call
	add sp,6

	push 1			; first number
	push 2			; second number
	push 3			; third number (sum is 6)

	call findSum		; second call
	add sp,6	

	push 2			; first number
	push 4			; second number
	push 7			; third number (sum is D)

	call findSum 		;third call
	add sp,6
	mov ax, 0x4c00
	int 0x21
