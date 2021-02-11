	;; l19-1196 BCS-3E
	;; Code of project phase-1
	;; in future I would use interrupt
	
[org 0x0100]
	jmp start

clearScreen:
	push bp
	mov bp,sp
	push ax
	push es
	push di
	push cx

	mov ax, 0xb800
	mov es,ax
	mov di,0
	mov ah,0x00
	mov al,0x20
	mov cx,2000
	rep stosw
	;; screen has been cleared
	pop cx
	pop di
	pop es
	pop ax
	pop bp
	ret

short_delay:
	push ax
	push cx
	mov ax,0
small_loop:
	inc ax
	cmp ax,0x0FFF
	jb small_loop
	pop cx
	pop ax
	ret

delay:
	push ax
	push cx
	mov cx,0
	mov ax,0
bigLoop:
	inc ax
	cmp ax,0x0FFF
	jb bigLoop
	mov ax,0
	inc cx
	cmp cx,9		;runs the loop 10 times
	jb bigLoop
	pop cx
	pop ax
	ret
	
random_in_range:		;random_in_range(rnum,min,max)
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
while_not_in_range:
	call short_delay	       ;to update a timer
	MOV AH, 00h  ; interrupts to get system time        
	INT 1AH	     ;cx:dx hold now time
	mov ax,dx
	xor dx,dx
	mov cx,10
	div cx
	mov ax,[bp+4]		;high range
	cmp dx,ax
	ja while_not_in_range
	mov ax,[bp+6]		;low range
	cmp dx,ax
	jb while_not_in_range
	mov [bp+8],dx		;store the random number

	pop cx
	pop bx
	pop ax
	pop bp
	ret 4
	
	;; ==========================
draw_rectangle:
	;; draws the block in centre
	;; stack[length,height,fill_col,pos_x,pos_y,call,bp
	push bp
	mov bp,sp
	push ax
	push di
	push cx
	push bx
	
	mov ax,0xb800
	mov es,ax
	mov ax,160		;one line has 80 pixels
	mov bx,[bp+4]
	sub bx,1		; line-1
	mul bx			; 80*(line_number-1)+col

	mov di,[bp+6]		;column
	;; 	sub di,1		; because real is zero based 
	shl di,1		;word-size
	add di,ax		; actual initial position of rectangle
	mov ah,[bp+8]		; fill color
	mov al,223		;block is made up of blocks with color background
	
	mov bx,0
height:
	mov cx,[bp+12]		; length	
	cld			; left to right
	rep stosw

	push dx
	mov dx,80
	sub dx,[bp+12]
	shl dx,1	
	add di,dx
	pop dx
	add bx,1
	cmp bx,[bp+10]
	jb height
	
	pop bx
	pop cx
	pop di
	pop ax
	pop bp
	ret 10
	;; =============================== draw_bicks_layer
draw_bricks_layer:		;e.g function(layer1,color)
	push bp
	mov bp,sp
	push ax
	push cx
	push bx

	mov cx,0		;left most col
while_incomplete:
	mov ax,cx
	add ax,10		; 10 is max size of a brick
	cmp ax,80
	ja last_brick_remaining
	;; get random length on interval [5,10]
	call short_delay	; to bring randomness
	
	push 0			; random is stored her
	push 5
	push 10			;it is max size of bricks
	call random_in_range
	pop ax			;length comes here
	mov bx,ax		;store ax
	;; call draw_rectangle(length,height,fill_col,pos_x,pos_y)
	push ax			;length
	mov ax,1		; height of rectangle
	push ax			;height of rectangle
	mov ax,[bp+4]		;fill color of rectangle
	push ax
	push cx			;cx holds the pos of left-top rectangle
	mov ax,[bp+6]		;line number as y pos
	push ax
	call draw_rectangle
	;; update the length of wall
	add cx,bx
	add cx,1		;space between bricks
	;; restoring the registers
	jmp while_incomplete
last_brick_remaining:
	mov ax,80
	sub ax,cx
	push ax			;length
	mov ax,1
	push ax			;height of rectangle
	mov ax,[bp+4]		;fill color of rectangle
	push ax
	push cx			;cx holds the pos of left-top rectangle
	mov ax,[bp+6]		;line number as y pos
	push ax
	call draw_rectangle

	
	pop bx
	pop cx
	pop ax
	pop bp
	ret 4

reset_game:
	push bp
	mov bp,sp
	push ax
	push cx
	mov cx,0		; bricks starts from 
while:	
	mov ax,cx
	add ax,1
	push ax		;first line number 1 not zero
	shl ax,4	;make new color (works upto

	push ax
	call draw_bricks_layer
	inc cx
	cmp cx,4		; has 4 lines been printed
	jb while
	
	pop cx
	pop ax
	pop bp
	ret 2
draw_bounce_board:
	push bp
	mov bp,sp
	push ax
	push bx
	push cx

	;; pass argument to draw_rectangle
	push 10			;lenght of bounce board
	push 1			;height
	push 0x10		;color
	mov ax,[bp+4]		;x-pos
	push ax
	push 25		;y-pos, last row
	call draw_rectangle
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2

draw_ball:
	push bp
	mov bp,sp
	push ax
	push bx
	push cx

	mov ax,0xb800
	mov es,ax
	mov ax,160
	mov bx,[bp+4]		;y-pos
	mul bx			;160*y
	mov bx,[bp+6]		;x-pos
	add ax,bx		;160*y+x
	mov di,0		;points to left-top
	add di,ax		;the actual pos of ball

	mov ah,0x07
	mov al,178		;ball shape
	mov [es:di],ax
	add di,2		;enlarge ball
	mov [es:di],ax
	
	pop cx
	pop bx
	pop ax
	pop bp
	ret 4
	;; =============================== main	

start:
	;; stack[length,height,fill_col,pos_x,pos_y
	call clearScreen
	call reset_game
	
	push 40			;x-pos of board, y=25
	call draw_bounce_board
	
	push 40			;x-pos of ball
	push 10			;y-pos of ball
	call draw_ball

	mov ax, 0x4c00
	int 0x21
