[org 0x0100]
	jmp start

sub1:
	push bp
	mov bp,sp
	push ax
	push bx
	push cx

	mov ax,[bp+6]
	mov bx,[bp+4]
	add ax,bx
	mov [bp+8],ax

	pop cx
	pop bx
	pop ax
	pop bp
	
	ret 4

crtime:
	;; [time,p1,p2,...,pn,sub1,np,call,bp
	push bp
	mov bp,sp
	push ax
	push bx
	;; push cx  ; it will modified as per requirement
	push si
	
	mov cx,[bp+4]		; n parameters
	mov si,cx		; si = n
	shl si,2		; si = 2*n
	
pap:
	;; push all parameters
	mov ax,[bp+si]
	sub si,2
	dec cx
	cmp cx,0    
	jne pap
	call [bp+6]
	pop cx

	mov ax,[bp+4]
	shl ax,1
	
	pop si
	pop bx
	pop ax
	pop bp
	
	
	
start:
	push 0
	mov ax,5
	push ax
	mov ax,7
	push ax
	call sub1
	pop ax
	
	mov ax,0x4c00
	int 21h
	
	
