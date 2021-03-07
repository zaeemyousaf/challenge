	;; L19-1196 Zaeem Yousaf
	;; lab 7
	;; compiled and test on linux successfully
	[org 0x0100]
	jmp start

delay:
	push ax
	mov ax,0
bigLoop:
	inc ax
	cmp ax,0xEFFF
	jb bigLoop

	pop ax
	ret
animate:
	;; revolve asteric on the screen
	;;  swap left to right first
	;; stack [symbol,call,bp,di
	push bp
	mov bp,sp
	push di
	

	mov di,0		; 
leftToRight:
	call clearScreen
	push di			; location parameter
	push word[bp+4]		; symbol parameter 
	call displaySymbolAt	; diplay all chars with in given range
	add di,2		; move to next char
	call delay		; to create animation effect
	cmp di,160		; check right boundary
	jb leftToRight

	mov di,158
topToBottom:
	call clearScreen
	push di			; location parameter
	push word[bp+4]		; symbol parameter 
	call displaySymbolAt	; diplay all chars with in given range
	add di,160		; move to next char
	call delay		; to create animation effect
	cmp di,4000		; check right bottom boundary
	jb topToBottom

	mov di,4000
rightToLeft:
	call clearScreen
	push di			; location parameter
	push word[bp+4]		; symbol parameter 
	call displaySymbolAt	; diplay all chars with in given range
	sub di,2		; move to next char
	call delay		; to create animation effect
	cmp di,	3842		; check left bottom boundary
	ja rightToLeft
	
bottomToTop:
	call clearScreen
	push di			; location parameter
	push word[bp+4]		; symbol parameter 
	call displaySymbolAt	; diplay all chars with in given range
	sub di,160		; move to next char
	call delay		; to create animation effect
	cmp di,0		; check left bottom boundary
	ja bottomToTop

	pop di
	pop bp
	ret 2			; free symbol parameter


clearScreen:
	push ax
	push es
	push di

	mov ax, 0xb800 ; load video base
	;;inc ax
	mov es, ax ; point es to video base
	mov di, 0 ; point di to top left column
nextSpace: mov word [es:di], 0x0020 ; clear next char on screen
	add di, 2 ; move to next screen location
	cmp di, 4000 ; has all ascii char been printed
	jne nextSpace ;
	pop di
	pop es
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
	call clearScreen	
	push 42			; push symbol
	call animate		;

	mov ax, 0x4c00 ; terminate program
	int 0x21
