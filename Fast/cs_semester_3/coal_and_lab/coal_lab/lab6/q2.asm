	[org 0x0100]
	jmp start
summation:
	;; [result,r,l,call,bp,
	push bp
	mov bp, sp
	mov cx, [bp+4]		; cx = l
	mov bx,0		; whole sum
	
wlg:
	;; while l greater
	cmp cx,0
	jbe endwlg
	push 0			; result of power
	push word [bp+6]		; base
	push cx			; l
	call power
	pop ax			;
	add bx, ax		;
	dec cx
	jmp wlg
endwlg:
	;; end while l greater than zero
	mov [bp+8], bx
	pop bp
	ret 4
power:
	push bp
	mov bp,sp		;[0,base,power,call,bp,ax,cx]
	push ax
	push cx

	mov cx,[bp+4]
	mov ax,1

while:
	cmp cx,0
	jbe endWhile
	mul word [bp+6]
	dec cx
	jmp while
	
endWhile:	
	mov [bp+8],ax
	;; restore values
	pop cx
	pop ax
	pop bp
	ret 4
start:

	push 0			; result of summation should be 'E'
	push 2			; r=2
	push 3			; l=1,2,3
	call summation
	pop ax
	
	mov ax,0x4c00
	int 0x21
