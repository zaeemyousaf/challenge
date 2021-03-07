; Activity 5
	;;  rotating values of registers
	;;  using fourth register for swapping puporse
[org 0x0100] ; directive
mov ax,10    ; move 10 in regist ax
mov bx,20    ; move 20 in register bx
mov cx, 30    ; move 30 in register cx

mov dx, ax			; copy ax into bx (dx is 10)
mov ax, cx			;copy cx into ax( ax is 30)
mov cx, bx			;copy bx into cx (cx is 20)
mov bx, dx			;copy dx into bx (bx is 10)
;; all values have been rotated
mov ax, 0x4c00 ;terminate the program
int 0x21
