; Author: Zaeem Yousaf (19L-1196 3E2) Homework 1
; find min of the array of 10 int
; register ax will hold the min
; register bx will fetch the int from array
; register bp will point toward the array
; initially, first int will be considered min
; then it will be updated after comparison
; cx will act as counter
; di will point to min 

[org 0x0100]
jmp start 

array:
	dw 9,7,2,3,1,6,20,5,6,29
length:
	dw 0
	
min:	dw 0
start:
	mov di, min		; destination index points to min
	mov cx, [length]	; set cx to length
	add cx,0		; for zero flag
	jz exit			; if length=0 then exit
	mov bp, array		; point bp to array's first element
	mov bx, [bp]		; bx hold first element
	mov ax, bx		; ax assumes to have the smallest int
	sub cx,1		; decrement cx
	add bp, 2		; now bp points to next element
		
while:
	cmp cx,0		; cx == 0
	je exit			; jump if cx = 0
	
	mov bx, [bp]		; bx hold first element
	cmp bx, ax		; compare ax and bx
	jb assignNewValue	; jump if bx < ax

	sub cx,1		; decrement cx
	add bp, 2		; now bp points to next element
	jmp while
	
assignNewValue:
	mov ax, bx		; assign new value to ax
	sub cx,1		; decrement cx
	add bp, 2		; now bp points to next element
	jmp while		; unconditional jump to exit 
	
exit:
	mov [di], ax		; store the min
	mov ax, 0x4C00
	int 0x21
