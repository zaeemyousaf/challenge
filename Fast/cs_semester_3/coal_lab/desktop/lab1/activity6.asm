; Activity 6

[org 0x0100] ; directive
mov ax, 6    ; 6 is moved into ax register
add ax,6    ; ax is now 12
add ax,6    ; ax is now 18
add ax,6    ; ax is now 24
add ax,6    ; ax is now 30
add ax,6    ; ax is now 36

mov ax, 0x4c00 ;terminate the program
int 0x21
