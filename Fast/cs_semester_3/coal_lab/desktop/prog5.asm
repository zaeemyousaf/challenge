
	[org 0x0100]
	jmp start	
	;; pass an array and its length
	;; compute its average by calling 'average'
	;; average calles 'findSum'
	;; result is stored in ax
array:	dw 1, 2, 3, 3, 4, 11
length:	dw 6

array2:	dw 1, 2, 3, 3, 4, 11,12,13,14,17
length2:	dw 10
	
findSum:
	;; [avg,array_add,length,call_next,sum,call_find_next,bp,ax,si,cx]

	push bp
	push ax
	push si
	push cx
	;; 	[10,20,30,call_next,pb,ax]
	mov bp,sp		;sp and bp points to cx
	mov ax,0		; ax is initialized to zero
	mov si,[bp+16]		; si points to array
	mov cx,[bp+14]		; cx holds the length
	
whileRemaining:	
	add ax,[si]		; adding each element into ax
	add si,2		; si now points to next element
	dec cx			; decrement cx
	cmp cx,0		; cx ==0
	jne whileRemaining	;read until cx is zero
	;; restore values of pb and ax
	mov [bp+10],ax		; cumulative sum 
	pop cx
	pop si
	pop ax
	pop bp
	ret

average:
	push 0			; for total sum 
	call findSum
	push bp			;
	push ax			;
	;; [0,array_add,length,call_next,sum,bp,ax]
	mov bp,sp		; bp pointing at ax
	mov ax,[bp+4]		; now ax holds sum
	div byte [bp+8]		; sum/length	
	mov [bp+12],al		; store quotient

	;; resotre the values
	pop ax
	pop bp
	add sp,2
	ret
start:
	;; first call with parameters
	push 0			; average result
	push word array
	push word [length]
	call average
	add sp,4
	pop ax			; ax holds now the average

	;; second call with parameters	
	push 0			; average result
	push word array2
	push word [length2]
	call average
	add sp,4
	pop ax			; ax holds now the average
	

	mov ax, 0x4c00
	int 0x21
