	[org 0x0100]
	jmp start
	;;  primes between a and b (give as parameter)
	;;  concept of stack
n:	dw 0			; total number of primes

isprime:
	;; wheather last number pushed on the stack is prime
	push bp			;
	push cx			; is counter
	push ax			; ax will hold fetched value

	mov bp,sp		;
	mov cx,1		; every number is divisible by 1

while:
	;; [number,bp,cx,ax]
	cmp cx,[bp+6]		;
	jb while
	

getNextNumber:
	
primesBetween:

whileLessThanB:
	;; inc a
	call isprime
	pop ax			; if 1 then prime
	cmp ax,1		; ax==1
	jne getNextNumber
	mov ax,[n]
	add ax,1
	mov [n],ax
	;;  cmp running number with b
	push bp
	mov bp, sp
	cmp [bp],[bp+2]
	pop bp
	jne getNextNumber
	jmp whileLessThanB
	ret
	
start:
	push 10			;a
	push 20			;b
	call primesBetween
	;; look at n for updated values
	
	mov ax, 0x4c00
	int 0x21
