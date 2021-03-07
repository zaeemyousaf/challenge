	;; take user input and move a character horizontally
	
[org 0x0100]
	jmp start
	
;;; customization features
block_length:	dw 20		; ----
back_color:	 db 0x71
bricks_width:	dw 1		; the height of brick is 2 char or 2 lines
entity_color:	db 0x17
ball_symbol:	db 'o'
initial_angle:	db 30		; clockwise, 90 for vertical
bricks:				;;not_destroyed,pos,length,not_destroyed,...
	dw 1,1,5
	dw 1,7,10
	dw 1,18,5
	dw 1,24,10
	dw 1,35,5
	dw 1,41,10
	dw 1,52,5
	dw 1,58,10
	dw 1,69,5
	dw 1,75,5
bricks2:				;;not_destroyed,pos,length,not_destroyed,...
	dw 1,1,10
	dw 1,11,5
	dw 1,17,10
	dw 1,28,5
	dw 1,34,10
	dw 1,45,5
	dw 1,51,10
	dw 1,62,5
	dw 1,68,10
clearScreen:
	push bp
	mov bp,sp
	push ax
	push es
	push di
	push cx

	;; draw one char on left most column
	mov ax, 0xb800
	mov es,ax
	mov di,0
	mov ah,[back_color]
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

	
random_in_range:
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
while_not_in_range:	
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
	

	;; update location
	;; draw char
	;; make delay
	;; clear screen by drawing overlay
	;; loop again

	;; ;; draw one char on left most column
	;; mov ax, 0xb800
	;; mov es,ax
	;; mov di,0
	;; mov ah,[back_color]
	;; mov al,0x20
	;; mov cx,2000
	;; rep stosw
	;; screen has been cleared

draw_rectangle:
	;; draws the block in centre
	;; stack[length,width,fill_col,pos_x,pos_y,call,bp
	push bp
	mov bp,sp
	push ax
	push di
	push cx
	push bx
	
	mov ax,0xb800
	mov es,ax
	mov ax,80		;one line has 80 pixels
	mov bx,[bp+4]
	sub bx,1		; line-1
	mul bx			; 80*(line_number-1)+col

	mov di,[bp+6]		;column
	sub di,1		; because real is zero based 
	shl di,1		;word-size
	add di,ax		; actual initial position of rectangle
	
	mov ah,[bp+8]		; fill color
	mov al,' '		;block is made up of spaces with color background
	
	mov bx,0
width:
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
	jb width

	pop bx
	pop cx
	pop di
	pop ax
	pop bp
	ret 10

make_bricks:			;draw 4 lines of bricks
	;; [brickrow,col,bp
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push di
s	push es
	push si			;

	mov si,[bp+6]		;will point towards bricks
	mov cx,0		;bricks counter
show_all_bricks:
	push word [si+4]		;length
	push word [bricks_width]	;
	push word [bp+4]		;red color with white forground
	push word [si+2]		;x-pox
	push word 1			;on first line
	call draw_rectangle
	call delay
	add si,6
	inc cx
	cmp cx,10
	jb show_all_bricks

	pop si
	pop es
	pop di
	pop cx
	pop bx
	pop ax
	pop bp

	ret 

next_pos:	;routine: next_pos(new_pos,new_velocity,old_pos,old_velocity)
	;; stack[new_x,new_y,new_v_x,new_v_y,old_x,old_y,old_v_x,old_v_y,call]
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx

	
start:
	;; ------------------
	;; push 0			;random number
	;; push 5			; min
	;; push 10			; max
	;; call random_in_range
	;; pop ax
	
	;; ------------------

	;; stack[length,width,fill_col,pos_x,pos_y,call
	call clearScreen
	mov ax,bricks2
	push ax
	mov ax,0x47
	push ax
	call make_bricks

	;; mov ax,5		;length 5 chars long
	;; push ax
	;; mov ax,2		;width 2 chars
	;; push ax
	;; mov ax,0x47		;fill color
	;; push ax
	;; mov ax,1		; on first column
	;; push ax
	;; mov ax,1		; on first row (one based index)
	;; push ax
	;; call draw_rectangle

	;; mov ax,1		;length 5 chars long
	;; push ax
	;; mov ax,2		;width 2 chars
	;; push ax
	;; mov ax,0x77		;fill color
	;; push ax
	;; mov ax,6		; on first column
	;; push ax
	;; mov ax,1		; on first row (one based index)
	;; push ax
	;; call draw_rectangle

	;; mov ax,5		;length 5 chars long
	;; push ax
	;; mov ax,2		;width 2 chars
	;; push ax
	;; mov ax,0x47		;fill color
	;; push ax
	;; mov ax,7		; on first column
	;; push ax
	;; mov ax,1		; on first row (one based index)
	;; push ax
	;; call draw_rectangle	
	
	;; call show_all_bricks
	;; stack[symbol,pos,call
	
	
	
;; 	mov cx,0
;; move_leftward:	
;; 	mov ah, 0x07
;; 	mov al, [block_symbol]

;; 	push cx
;; 	mov cx,0
;; draw_rectangle:
;; 	mov word [es:di],ax
;; 	sub di,2
;; 	inc cx
;; 	cmp cx,[block_length]
;; 	jb draw_rectangle

;; 	call delay
;; 	mov cx,0
;; delete_block:
;; 	mov word [es:di],0x0720
;; 	add di,2
;; 	inc cx
;; 	cmp cx,[block_length]
;; 	jb delete_block

;; 	shl cx,1		; pos of next 
;; 	sub di,cx

;; 	pop cx
	
;; 	inc cx
;; 	push ax
;; 	push cx
	
;; 	mov ax,cx
;; 	mov cl,[block_length]	;80/4
;; 	div cl

;; 	pop cx
;; 	cmp cx, ah
	
;; 	jb move_leftward
;; right_ward:	
;; 	mov ah, 0x07
;; 	mov al, [block_symbol]
;; 	mov word [es:di],ax

;; 	add di,2
;; 	mov word [es:di],ax
;; 	call delay

;; 	mov word [es:di],0x0720
;; 	sub di,2
;; 	mov word [es:di],0x0720
;; 	add di,4
;; 	dec cx
;; 	cmp cx,0
;; 	ja right_ward
;; 	jmp move_leftward
	mov ax, 0x4c00
	int 0x21
