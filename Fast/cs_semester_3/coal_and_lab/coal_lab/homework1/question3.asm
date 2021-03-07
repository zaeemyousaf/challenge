	;; Author: Zaeem Yousaf (19L-1196 3E2) Homework 1
	;;  nth bit which is to be complemented
	;;  is read in ax register
	;;  bx holds the actual valued to be complemented
	;;  cx contains initial mask to 000000000 000000001
	;;  then cx is shifted n-1 times left
	;;  then mask is applied with xor 
	[org 0x0100]
	jmp start
nthBitToComplement: dw 10			; from least signifiant
toComplement:	 dw 0xAF02				; the number to be complemented
start:
	mov ax, [nthBitToComplement]	; ax has the vlaue of number
	mov bx, [toComplement]		; bx holds  10101111 0000 0010
	mov cx, 1			; cx holds mask 00000000 00000001
shiftLeft:
	cmp ax,1		; shift left (n-1) times because 1 is already at 1
	je applyMask
	shl cx, 1
	sub ax, 1
	jmp shiftLeft
applyMask:
	xor bx, cx			; xor operation on bx
	mov [toComplement], bx	; store new value
	
	mov ax, 0x4c00
	int 0x21
