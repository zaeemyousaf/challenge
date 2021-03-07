[org 0x100]

jmp start

; print string using bios service
[org 0x0100]
jmp start
message: db 'Happy number'
counter: dw 0
sum: dw 0

oldisr: dd 0 ; space for saving old isr
; keyboard interrupt service routine
kbisr: push ax
push es
mov ax, 0xb800
mov es, ax ; point es to video memory
in al, 0x60 ; read a char from keyboard port
cmp al, 0x2a ; is the key left shift
jne nextcmp ; no, try next comparison
mov byte [es:0], 'L' ; yes, print L at top left
jmp nomatch ; leave interrupt routine
nextcmp: cmp al, 0x36 ; is the key right shift
jne nomatch ; no, leave interrupt routine
mov byte [es:0], 'R' ; yes, print R at top left
nomatch: ; mov al, 0x20
; out 0x20, al
pop es
pop ax
jmp far [cs:oldisr] ; call the original ISR
; iret

get_sqr_sum: ; takes input as
; and computes till single digit is acheived
; returns 1 if number of iterations are less than 256
push bp
mov bp, sp
push es
push ax
push bx
push cx
push dx
push di
;mov ax, 0xb800
;mov es, ax ; point es to video base
mov ax, [bp+4] ; load number in ax
mov [sum],ax
mov bx, 10 ; use base 10 for division
mov cx, 0 ; initialize count of digits
nextdigit: mov dx, 0 ; zero upper half of dividend
div bx ; divide by 10
;add dl, 0x30 ; convert digit into ascii value

push dx ; save ascii value on stack
inc cx ; increment count of values
cmp ax, 0 ; is the quotient zero
jnz nextdigit ; if no divide it again
;mov di, 140 ; point di to 70th column
nextpos: pop dx ; remove a digit from the stack
mov ax,dx
mov bx,[sum]
mov ax,dl
mul dl
add bx,ax
mov [sum],bx

;mov dh, 0x07 ; use normal attribute
;mov [es:di], dx ; print char on screen
;add di, 2 ; move to next screen location
loop nextpos ; repeat for all digits on stack
pop di
pop dx
pop cx
pop bx
pop ax
pop es
pop bp
ret 2


is_happy:
push bp
mov bp,sp
push ax
push bx
push cx

mov cx,0
mov ax,[counter]
add ax,1
mov [counter],ax

mov ax,[bp+4]
push ax
call get_length
pop bx
cmp bx,1
ja further_reduce
;base case
mov ax,[counter]
cmp ax,256

happy_number:
	mov [bp+6],1
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2

not_happy_number:
	mov [bp+6],0
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2

further_reduce:
	push 0	;flag to check whether it is happy or not
	push ax
	call is_happy

clrscr: push es
push ax
push cx
push di
mov ax, 0xb800
mov es, ax ; point es to video base
xor di, di ; point di to top left column
mov ax, 0x0720 ; space char in normal attribute
mov cx, 2000 ; number of screen locations
cld ; auto increment mode
rep stosw ; clear the whole screen
pop di
pop cx
pop ax
pop es
ret

printstr:
call clrscr
mov ah, 0x13 ; service 13 - print string
mov al, 1 ; subservice 01 – update cursor
mov bh, 0 ; output on page 0
mov bl, 7 ; normal attrib
mov dx, 0x0A03 ; row 10 column 3
mov cx, 11 ; length of string
push cs
pop es ; segment of string
mov bp, message ; offset of string
int 0x10 ; call BIOS video service

start: 


; xor ax, ax
; mov es, ax ; point es to IVT base
; mov ax, [es:9*4]
; mov [oldisr], ax ; save offset of old routine
; mov ax, [es:9*4+2]
; mov [oldisr+2], ax ; save segment of old routine
; cli ; disable interrupts
; mov word [es:9*4], kbisr ; store offset at n*4
; mov [es:9*4+2], cs ; store segment at n*4+2
; sti

	
;mov ah, 0 ; service 0 – get keystroke
;int 0x16 ; call BIOS keyboard service
mov ax,0x4c00
int 21h