	;;  read an array
	;;  square each term and store it in same array
	;;  written for practice in FAST university
[Org 0x0100]		; initialize the program

	mov si,array		; si will point toward ar
	ray
	mov bx,[n]		; total numbers in bx
readArray:	
	mov ax, [si]		; ax holds contents of si
	mov cx, ax		; set counter to ax
	sub cx, 1		; one time has been added
square:
	cmp cx, 0		; cx == 0
	je store		; if true then jump to label: store
	add ax, [si]		
	sub cx, 1
	jnz square		; jump if not zero ( jump square if cx==0)

store:	mov [si], ax		; store back
	add si, 2		; point to next int
	sub bx,1
	jnz readArray
	
	Mov ax, 0x4c00		; terminate the proram
	int 0x21
	
array:	dw 1,2,3,4,5,6,7,8,9,10
n:	dw 10
