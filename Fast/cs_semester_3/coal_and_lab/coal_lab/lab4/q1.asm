[ORG 0x0100]
jmp start

num_ax: dw 10
num_bx: dw 0x000F
one_counter: dw 0
ans: dw 0
	
start:
	mov cx, 0
	mov bx, [num_bx];
	mov ax, [num_ax];

read_next:
	add cx, 1
	cmp cx, 16
	je exit
	mov dx,cx
	shl dx,1
	test bx,dx
	jz read_next
	add word [one_counter],1
	jmp read_next
	
exit:
	mov cx, [one_counter]
	mov bx, 0xFFFF
	jmp l1
l1:
	shr bx, 1
	sub cx,1
	jnz l1
	; now mask is read to be applied
	xor ax, bx
	mov [ans], ax

	MOV  AX, 0x4C00         ; Terminate Program 
	INT  0x21               
