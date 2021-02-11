[org 0x0100]
	jmp start
	
str1:	db 'smaller string',0 ; null terminated strings
str2:	db 'this is big larger',0
larger:	db '                            '
smaller: db '                              '

strLength:			; taken from q3
	push bp
	mov bp,sp
	;; stack[length,str,call,bp,ax,cx,di,
	push ax
	push cx
	push di
	push ds
	pop es

	mov di,[bp+4]		; pointing to string
	mov cx,0xFFFF		; assuming very large string
	mov al,0
	repne scasb
	mov ax,0xFFFF
	sub ax,cx
	dec ax
	mov [bp+6],ax		; store length
	;; restore local variables
	pop di
	pop cx
	pop ax
	pop bp
	ret 2
	
strcmp:
	push bp
	mov bp,sp
	;; stack[ds,str1,ds,str2,call,bp,ds,es,di,si,cx
	;; store the states of local variables
	push ds
	push es
	push di
	push si
	push cx

	lds si,[bp+4]
	les di,[bp+8]

	push ds
	push si
	call strLength		; written in q3
	pop ax			; length of first str

	push es
	push di
	call strLength		; length of str2
	pop cx

	cmp cx,ax		; compare on basis of length
	ja cx_larger		; exit and set flag zero

	mov ax,1		; assuming comparison true
	repe cmpsb
	je exit
	
cx_larger:
	;; es:di should point to larger as detination
	push es
	push di
	push ds
	push si
	;; stack[ds,str1,ds,str2,call,bp,ds,es,di,si,cx,es,di,ds,si
	mov di,larger
	mov si,[bp-6]

	pop si
	pop ds
	pop di
	pop es
	mov ax, 0		; returning zero
exit:
	;; restore local variables
	pop cx
	pop si
	pop di
	pop es
	pop ds
	pop bp
	ret 8
start:
	mov ax,0
	push ds
	mov ax,str1
	push ax

	push ds
	mov ax,str2
	push ax
	call strcmp		; watch ax after execution
		
	mov ax, 0x4c00
	int 0x21
