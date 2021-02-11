	[org 0x0100]
	;; push all elements of array in stack
	;; then add all elements and store in dx
	jmp start
array:
	dw 1, 2, 3, 4, 5,0
		
start:
	mov cx,0		; counter 
	mov bx, array
	mov ax,0		; initial ax =0
loop:
	cmp word [bx],0
	je poping
	push word [bx]
	add bx,2		;bx=bx+2
	inc cx			;cx++
	jmp loop
	
poping:
	cmp cx,0		; cx==0
	je exit
	pop dx			;
	add ax,dx		; ax = ax+dx commulative sum
	sub cx,1
	jmp poping
exit:
	mov dx,ax
	mov ax, 0x4c00
	int 0x21
