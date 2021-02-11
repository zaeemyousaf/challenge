	;; l19-1196 BCS-3E
	;; Code of project phase-1
	;; in future I would use interrupt
	
[org 0x0100]
	jmp start
moving_left:	db 'moving left'
moving_right:	db 'moving right'
moving_up:	db 'moving upside'
moving_down:	db 'moving down'
looping:	db 'it is in loop'

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
	push bx
	push cx
	push dx
	
	mov ax,0
small_loop:
	inc ax
	cmp ax,0x0FFF
	jb small_loop

	pop dx
	pop cx
	pop bx
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
	push dx
	
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

	pop dx
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
	mov al,223		;block is made up of blocks with color 		background
	
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
	push 2
	push 6			;it is max size of bricks
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
	push dx
	push es
	push si
	
	;; pass argument to draw_rectangle
	push 20			;lenght of bounce board
	push 1			;height
	push 0x10		;color
	mov ax,[bp+4]		;x-pos
	push ax
	push 25		;y-pos, last row
	call draw_rectangle

	pop si
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2

draw_ball:
	;; [color,x,y,call,bp
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	
	mov ax,0xb800
	mov es,ax
	mov ax,160
	mov bx,[bp+4]		;y-pos
	mul bx			;160*y
	mov bx,[bp+6]		;x-pos
	shl bx,1
	add ax,bx		;160*y+x
	mov di,0		;points to left-top
	add di,ax		;the actual pos of ball

	mov ah,[bp+8]		; color
	;; 	mov al,'o'
	mov al,219

	mov [es:di],ax
	add di,2
	mov [es:di],ax

	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 4
next_pos:
	;; [0,ax,cx,dx,call,bp
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	
	mov ax,[bp+8]		; ball pos
	mov bx,ax		; nex-pos
	mov cx,[bp+6]		; ball speed
	mov dx,[bp+4]		; ball direction
	cmp dh,0		; is x-dir negative
	jne x_pos
	sub bh,ch
	jmp check_y
x_pos:
	add bh,ch
check_y:
	cmp dl,0
	jne y_pos
	sub bl,cl
	jmp all_cases_handled
y_pos:
	add bl,cl
all_cases_handled:	
	mov [bp+10],bx		;	
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 6
		
destroy_brick:
	;; destroy_brick(x,y)
	;; [xy,call,bp
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	push es
	push si

	mov ax,0xb800
	mov es,ax

	mov ax,[bp+4]		;xy
	shl ax,8		; y is in lower byte (discarding higer part)
	shr ax,8		; higer part discarded
	mov bh,80
	mul bh			;80*y
	mov bx,[bp+4]		;xy
	shr bx,8			;x is in upper byte
	add ax,bx		;(80*y)+x
	shl ax,1			;2(80*y+x) actual position

	mov di,ax
	mov cx,di		;
	add cx,2		;this side will be cleared by delete_right


delete_left:
	;; deletes left part of brick
	mov ax,[es:di]		; pos to be deleted
	cmp al, ' '		; compare with
	je delete_right
	mov ah, 0x00		; black color both foreground and background
	mov al, ' '		;
	mov [es:di],ax		;write back 
	sub di,2
	jmp delete_left		;
	
delete_right:
	mov di,cx		; cx holds the right part to be deleted
	;; deletes right part of brick
delete_further:	
	mov ax,[es:di]		; pos to be deleted
	cmp al, ' '		; compare with
	je eob
	mov ah, 0x00		; black color both foreground and background
	mov al, ' '		;
	mov [es:di],ax		;write back 
	add di,2
	jmp delete_further		;
eob:
	;; end of brick
	pop si
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2

brick_test:
	;; brick_test(bool,xy)
	;; [0,ax,call,bp
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	push es
	push di

	mov ax,0xb800
	mov es,ax
	
	mov ax,[bp+4]		;xy
	shl ax,8		; y is in lower byte (discarding higer part)
	shr ax,8		; higer part discarded
	mov bh,80
	mul bh			;80*y
	mov bx,[bp+4]		;xy
	shr bx,8			;x is in upper byte
	add ax,bx		;(80*y)+x
	shl ax,1			;2(80*y+x) actual position

	mov di,ax		;
	mov ax,[es:di]		; pixel	
	cmp byte al, ' '		; is color black
	;; comparison could also be made by space character
	jne not_brick
	mov word [bp+6],1
	jmp end_brick_test
not_brick:
	mov word [bp+6],0
end_brick_test:
	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2
	
start_game:
	;; animation part	
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx

	call delay
	push 0			;
	push 0			; random direction
	push 1
	call random_in_range	; random for x-dir
	pop ax			;

	;; dx holds direction
	;; 	mov dh,1
	mov dh,al		; x-dir
	mov dl,0		; y-dir is neg initially
	call delay
	push 0			; random x-velocity
	push 1
	push 2
	call random_in_range
	pop ax
	;; cx holds ball speed
	mov ch,al		; x-speed
	mov bx,2		;max speed
	sub bx,ax
	mov cl,bl		; y-speed
	;; ax hols ball.xy
	mov ah,40	      ; ball.x
	mov al,24	      ; ball.y
	;; bx holds the ball.next.pos
	
while_not_over:	
	push 0			;next-pos
	push ax			;current-pos
	push cx			;speed
	push dx			;direction
	call next_pos
	pop bx
		
check_left:	
	cmp byte dh,0
	je ball_moving_left
check_right:	
	cmp byte dh,1
	je ball_moving_right
check_up:	
	cmp byte dl,0
	je ball_moving_up
check_down:	
	cmp byte dl,1
	je ball_moving_down
	jmp keep_moving

ball_moving_left:
	;; check left boundary
	cmp byte bh,80		; if it becomes negative, very large number
	;; 	jb check_right
	jb is_brick_on_left
	;; otherwise perform reflection
	mov dh,1		;reflect x-axis only
	mov ah,0
	mov bh,0
	jmp keep_moving		; reflection has been handled
	
is_brick_on_left:
	push si			;save state
	push 0			;
	push ax
	call brick_test
	pop si
	cmp si,1		; 1:true
	pop si			; restore state
	jne check_right
	;; collision with brick has occured
	;; check whether 'top' or 'left' collision occured
	sub al,1		; ball.y - 1
	
	push si			;save state
	push 0			;
	push ax
	call brick_test
	pop si
	cmp si,1		; 1:true
	pop si			; restore state
	jne brick_on_top
	;; brick is on left
	;; reflect right by switching x-component only
	mov dh,1
	mov bx,ax		;next pos has been updated
brick_on_top:
	add al,1		; correct previos pos
	mov dl,1		; flip y-dir only
	mov bx,ax		; update brick next pos
	jmp keep_moving		; all cases handled
		
ball_moving_right:
	;; check right boundary
	cmp byte bh,79		; if it cross right boundary
	jb is_brick_on_right
	;; otherwise perform reflection
	mov dh,0		;reflect x-axis only
	mov ah,79
	mov bh,79
	jmp check_up
	
is_brick_on_right:
	push si			;save state
	push 0			;
	push ax
	call brick_test
	pop si
	cmp si,1		; 1:true
	pop si			; restore state
	jne check_up
	
	mov dh,0		;reflect x-axis only
	mov ah,79
	mov bh,79
	jmp keep_moving
	;; jmp check_up

ball_moving_up:
	;; check upper boundary
	cmp byte bl,25		; if it becomes negative, very large number	
	jb is_brick_on_top
	;; otherwise perform reflection
	mov dl,1		;reflect x-axis only
	mov al,0
	mov bl,0
	jmp check_down
is_brick_on_top:
	push si			;save state
	push 0			;
	push ax
	call brick_test
	pop si
	cmp si,1		; 1:true
	pop si			; restore si
	jne check_down
	mov dl,1		;reflect x-axis only
	mov al,0
	mov bl,0
	;; 	jmp check_down
	jmp keep_moving

ball_moving_down:
	;; check lower boundary
	cmp byte bl,25		; if it becomes negative, very large number
	;; jb keep_moving
	jb is_brick_on_bottom
	;; otherwise perform reflection
	mov dl,0		;reflect x-axis only
	mov al,24
	jmp keep_moving
	
is_brick_on_bottom:
	push si			;save state
	push 0			;
	push ax
	call brick_test
	pop si
	cmp ax,1		; 1:true
	pop si			; restore si
	jne keep_moving
	mov dl,0		;reflect x-axis only
	mov al,24
	jmp keep_moving

keep_moving:	
	push 0x07		;white color
	mov bh,00000000b			;
	mov bl,ah			;
	push bx			;x-pos of ball
	mov bh,00000000b			;	
	mov bl,al		;y-pos of ball
	push bx
	call draw_ball

	;; 	call delay
	call delay

	;; delete ball after delay
	push 0x00		;		black color same as screen background
	mov bh,00000000b			
	mov bl,ah			
	push bx			;			x-pos of ball
	mov bh,00000000b				
	mov bl,al		;		y-pos of ball
	push bx
	call draw_ball

	push ax
	call destroy_brick
	
	push 40			;x-pos of board, y=25
	call draw_bounce_board

	;; continue game
	push 0			;next-pos
	push ax			;current-pos
	push cx			;speed
	push dx			;direction
	call next_pos
	pop bx
	mov ax,bx		; pass next pos to ax
	;; bh = ah +/- ch
	;; bl = al +/- cl

	;; push ax
	;; call destroy_brick	

	jmp while_not_over
	
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret


	;; =============================== main		
start:
	;; stack[length,height,fill_col,pos_x,pos_y
	call clearScreen
	call reset_game

	;; push si			;store state
	;; push 0			;result
	;; mov si,0x0100
	;; push si
	;; call brick_test
	;; pop si
	;; cmp si,1
	;; pop si
	;; jne end

	call start_game		;
;; stop:
;; 	call delay
;; 	jmp stop
	;; mov ax,0x07 
	;; push ax
	;; mov ax,1
	;; push ax
	;; push 79
	;; push ax
	;; call draw_ball

	;; push 0
	;; push 0x2800
	;; push 0x0203
	;; push 0x0001
	;; call next_pos
	;; pop ax
end:	
	mov ax, 0x4c00
	int 0x21
