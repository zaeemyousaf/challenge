;This program displays a counter after every 10seconds

[org 0x0100]

jmp start
tickcount: dw 0
ten_sec: dw 0; This variable counts till ten seconds. You might want to work on this variable if there is a keyboard interrupt
count: dw 0; This variable is being printed. It may be useless for your solution.
message: db 'Screen saver is on now'
length: dw 22
running: dw 0

printstr: push bp
mov bp, sp
push es
push ax
push cx
push si
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov al, 80 ; load al with columns per row
mul byte [bp+10] ; multiply with y position
add ax, [bp+12] ; add x position
shl ax, 1 ; turn into byte offset
mov di,ax ; point di to required location
mov si, [bp+6] ; point si to string
mov cx, [bp+4] ; load length of string in cx
mov ah, [bp+8] ; load attribute in ah
nextchar: mov al, [si] ; load next char of string
mov [es:di], ax ; show this char on screen
add di, 2
add si, 1 ; move to next char in string
loop nextchar ; repeat the operation cx times
pop di
pop si
pop cx
pop ax
pop es
pop bp
ret 10

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


; subroutine to print a number at top left of screen
; takes the number to be printed as its parameter
printnum: push bp
mov bp, sp
push es
push ax
push bx
push cx
push dx
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov ax, [bp+4] ; load number in ax
mov bx, 10 ; use base 10 for division
mov cx, 0 ; initialize count of digits
nextdigit: mov dx, 0 ; zero upper half of dividend
div bx ; divide by 10
add dl, 0x30 ; convert digit into ascii value
push dx ; save ascii value on stack
inc cx ; increment count of values
cmp ax, 0 ; is the quotient zero
jnz nextdigit ; if no divide it again
mov di, 140 ; point di to 70th column
nextpos: pop dx ; remove a digit from the stack
mov dh, 0x07 ; use normal attribute
mov [es:di], dx ; print char on screen
add di, 2 ; move to next screen location
loop nextpos ; repeat for all digits on stack
pop di
pop dx
pop cx
pop bx
pop ax
pop es
pop bp
ret 2


; timer interrupt service routine
; This counts 10 seconds
timer: 
push ax
inc word [cs:tickcount]; increment tick count
cmp word [cs:tickcount], 18
je inc_sec
jmp skip
inc_sec:
mov word [cs:tickcount], 0
inc word[cs:ten_sec]
cmp word [cs:ten_sec], 5 ; i modified to save time
je print
jmp skip

print:
;We have reached 10 second threshold so now we'll call our desired subroutine
;===========
call clrscr
screen_saver:
mov ax, 30
push ax ; push x position
mov ax, 20
push ax ; push y position
mov ax,[running]
add ax,1
mov [running],ax
cmp ax,2000
jb red
cmp ax, 7000
jb green
;otherwise blue color
mov ax, 1 ; blue on black attribute
red:
mov ax,4
jmp color_decided
green:
mov ax,2
jmp color_decided

color_decided:
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr
jmp screen_saver

inc word [cs:count]
mov word [cs:ten_sec], 0
push word [cs:count]
;call printnum ; print tick count
; instead of printnum, you shall call your screensaver routine.

skip:
mov al, 0x20
out 0x20, al ; end of interrupt
pop ax
iret ; return from interrupt


start: 
xor ax, ax
mov es, ax ; point es to IVT base
cli ; disable interrupts
mov word [es:8*4], timer; store offset at n*4
mov [es:8*4+2], cs ; store segment at n*4+2
sti ; enable interrupts

;;=============== 
keep_running:
	jmp keep_running

mov dx, start ; end of resident portion
add dx, 15 ; round up to next para
mov cl, 4
shr dx, cl ; number of paras
mov ax, 0x3100 ; terminate and stay resident
mov ax,0x4c00
int 0x21