	[org 0x0100]
	jmp start	
	;; pass an array and store its sum in ax

array1:		dw 1500,3000,10,16,39,11,20,100
length1:	dw 8

array2:		dw 20,30,10,16,39,11,20,100,1,2,3,4
length2:	dw 12
	;; second array ends with 0
sum:
	mov bp,sp
	push ax
	
	mov bx,[bp+4]	     ; bx is pointing toward the array
	mov ax,0	     ; ax is initialized to zero
	mov cx,[bp+2]	     ; length stored in cx
while:	
	add ax,[bx]		; ax=ax+bx
	add bx,2		; now bx is pointing to next number
	sub cx,1		; decrement cx which is acting as counter
	cmp word cx, 0
	jne while
	mov [bp+6], ax

	pop ax			; restore the old value
	ret

start:
	push 0			; holds the sum of all
	push array1
	push word [length1]
	call sum
	add sp,4
	pop ax 			;total sum

	push 0			; holds the sum of all
	push array2
	push word [length2]
	call sum
	add sp,4
	pop bx 			;total sum

	add ax,bx		; sum of two arrays in ax
	
	mov ax, 0x4c00
	int 0x21
