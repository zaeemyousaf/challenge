	;; L19-1196 Zaeem Yousaf
	;; lab 7
	;; compiled and test on linux successfully
[org 0x0100]
	jmp start
; scroll up the screen
[org 0x0100]
jmp start
; subroutine to scroll up the screen
; take the number of lines to scroll as parameter
scrollUp:
	push bp
	mov bp,sp
	push ax
	push cs
	push si
	push di
	push es
	push ds

	mov ax,80
	mul byte [bp+4]
	mov si, ax
	push si
	shl si,1
	mov cx,2000
	sub cx, ax
	mov ax, 0xb800
	mov es,ax
	mov ds,ax
	xor di,di
	cld
	rep movsw
	mov ax, 0x0720
	pop cx
	rep stosw

	pop ds
	pop es
	pop di
	pop si
	pop cx
	pop ax
	pop bp
	
	ret 2

scrollDown:
	push bp
	mov bp,sp
	push ax
	push cs
	push si
	push di
	push es
	push ds

	
	mov ax,80
	mul byte [bp+4]
	push ax
	shl ax,1
	mov si, 3998
	sub si, ax
	mov cx, 2000
	sub cx, ax
	mov ax, 0xb800
	mov es,ax
	mov ds,ax
	mov di, 3998
	std
	rep movsw
	mov ax, 0x0720
	pop cx
	rep stosw

	pop ds
	pop es
	pop di
	pop si
	pop cx
	pop ax
	pop bp
	ret 2
delay:
	push ax
	mov ax,0
bigLoop:
	inc ax
	cmp ax,0xEFFF
	jb bigLoop

	pop ax
	ret
	
displaySymbolAt:
	push bp
	mov bp, sp
	push ax
	;; stack [location,symbol,call,bp,ax
	mov ax, 0xb800
	mov es,ax
	mov di,[bp+6]		; loation
	mov ah, 7		; white color, not blinking
	mov al, [bp+4]		; start of range

	mov word [es:di], ax	; write next char
	;; restore register values
	pop ax
	pop bp
	ret 4

start:	

	mov ax,3
	push ax
	call scrollDown

	call delay
	call delay
	call delay
	
	
	mov ax,3
	push ax
	call scrollUp

	call delay	
	call delay
	
	jmp start

	mov ax, 0x4c00 ; terminate program
	int 0x21
