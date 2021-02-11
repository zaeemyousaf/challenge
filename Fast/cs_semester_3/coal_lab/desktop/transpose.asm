	[org 0x0100]
	jmp start
	;; push all elements of array on stack
	;; in column wise order
	;; [1,3,5,7,2,4,6,8]
	;; pop and write back in reverse order


transpose:
	;; store old values
	push bp			;
	mov bp, sp		;
	push ax			; row counter
	push si			; array's address 
	push cx			; column counter
	push bx			;
	;; [array,call_transopose,bp,ax,si,cx,bx]
	mov ax,0		; zero row
	mov cx,0		; zeor col
	;; mov si, array
	mov si, [bp+4]
	mov bx,0		;
whileLessThanRows:
	push word [si]
	mov bx, [cols]		;
	add bx, bx		; mult by 2
	
	add si, bx		; si points to next row in same col
	inc ax			; row incremented
	
	cmp ax, [rows]		; compare ax with rows
	je whileLessThanCols	; jump if ax > rows
	jmp whileLessThanRows	; otherwise remain in same loop

whileLessThanCols:
	mov ax, 0
	mov bx,0		;	
	mov si, array  		;si is  pointing to array
	inc cx			; increment col
	add si, cx		; selecting specific column
	add si, cx		; selecting specific column
	cmp cx,[cols]		; compare cx with cols
	jb whileLessThanRows	;
	;; all columns have been read pushed
	mov bx, 0		;
	mov cx, [cols]		;
multiply:
	;;  multiply row by col by iteration sum
	add bx, [rows]		;
	dec cx
	cmp cx, 0
	ja multiply

	;; zero based index
	sub bx,1
	shl bx,1			; mult by 2 because data is word size
	mov si, array

writeback:
	pop ax
	mov [si+bx],ax
	sub bx, 2
	jae writeback
	;; changing the dimension of the array
	mov ax, [rows]		;
	mov bx, [cols]		;
	mov [rows], bx		;
	mov [cols], ax		;
	
	;;  array has been transposed
	pop bx	;
	pop cx			; column counter
	pop si			; array's address 
	pop ax			; row counter
	pop bp
	ret

start:
	push [rows]
	push [cols]
	push array
	call transpose
	
	mov ax, 0x4c00
	int 0x21
array:
	dw 1, 2
	dw 3, 4
	dw 5, 6
	dw 7, 8

rows: dw 4
cols: dw 2
	
