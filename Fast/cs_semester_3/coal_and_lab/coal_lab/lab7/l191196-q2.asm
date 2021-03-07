[org 0x0100]
	jmp start
Array: dw 1,2,3,4,5,6

findCounts:
	push bp
	mov bp, sp		;[counts,N,K,Arr,call,bp,ax,si,bx,cx
	push ax			; 
	push si
	push bx			; for addition of two cookies sweetnes
	push cx
	
	
whileNotEnt:
	mov cx,[bp+8]		; cx = N
	mov si,[bp+4]		; si points to Array
	;; always pick two elements
	mov ax,[si+2]		; second element
	mov bx,2
	mul bx
	add ax, [si]		; 1*x1 + 2*X2 

	mov bx, si+4		;
	sub cx,2
	mov ax, [bp+10]
	inc ax			; count++
insert:
	cmp ax, bx
	jb
	add bx,2
	jmp insert
	;; place found to insert
	mov [bx],ax
	;; shift all element to left one place	
	jmp whileNotEnd
	;restore old values of register
	pop cx
	pop bx
	pop si
	pop ax
	pop bp
	ret 6
	
	
start:
	push 0			; counts
	push 6			; N=6
	push 7			; k=7
	push word Arr		; 
	call findCounts
	mov ax, 0x4c00
	int 0x21