; Activity 4 ( summing up 5 entries of table 3)
	;; 3,6,9,12,15 (45)
; using approach 1 (only one register)
	;; using bx for commulative sum
	;; using ax for generating table of 3
[org 0x0100] ; directive
mov ax, 3    ;
mov bx, ax			; bx is now 3
add ax,3 			; now ax shoud be 6
add bx,ax			; bx is now 9
add ax,3 			; now ax shoud be 9
add bx,ax			; now bx is 18
add ax,3 			; now ax shoud be 12
add bx,ax			; now bx is 30
add ax,3 			; now ax shoud be 15
add bx,ax			; now bx is 45

mov ax, 0x4c00 ;terminate the program
int 0x21
