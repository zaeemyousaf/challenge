      	;; l19-1196 BCS-3E
	;; Code of project phase-4
	;; in future I would use interrupt
	
[org 0x0100]
	jmp start

oldisr:	dd 0
	
ball_x:	db 70			; init x pos of ball
ball_y:	db 24			; just above the bounce board
board_x:	db 0		; in mid of screen; y is fixed
ball_x_dir:	db 1			; 0: left; 1:right
ball_y_dir:	db 0			; 0: up; 1:down
life:	db 3				; initial 3 life
ball_size:	db 1			; 2 char long
game_out_flag:	db 0			; out when 1
board_length:	db 80

	


kbisr:
	pusha
	mov ax, 0xb800
	mov es,ax
	in al, 0x60
	cmp al, 0x36
	jne right_shift
	
	xor cx,cx
	mov ch,[board_x]
	inc cx
	mov [board_x],cx
	
right_shift:
	;; mov byte [es:0], 'L'
	cmp al,0x2a
	jne no_match_key

	xor cx,cx
	mov ch,[board_x]
	dec cx
	mov [board_x],cx
	
no_match_key:	
	;; mov byte [es:0], 'R'
	mov al,0x20
	out 0x20,al
	popa

	jmp far [cs:oldisr]
	;; 	iret			;

ref_x_brick:

	;; get reflection in x-axis of brick	
	;; just flips ball_x_dir
	;; no parameters given. it access global vars
	;; store states
	push ax
	push bx	

	push 6
	call printnum
	
	mov ah,0x1		; mask
	mov bh,[ball_x_dir]
	xor ah,bh		; inversion by complement
	mov [ball_x_dir], ah	; put back
	;; restore previous states
	pop bx
	pop ax
	ret

ref_y_brick:
	;; get reflection in y-axis of brick
	;; just flips ball_y_dir
	;; no parameters given. it access global vars
	;; store states
	push ax
	push bx	

	push 5
	call printnum
	
	mov ah,0x1		; mask
	mov bh,[ball_y_dir]
	xor ah,bh		; inversion by complement
	mov [ball_y_dir], ah	; put back
	;; restore previous states
	pop bx
	pop ax
	ret

ref_x_wall:

	;; get reflection in x-axis of wall
	;; just flips ball_x_dir
	;; no parameters given. it access global vars
	;; store states
	push ax			;store state
	push bx

	xor ax,ax
	mov ah,[ball_x_dir]
	;; if ball is moving left
	;; chage dir and set the ball on left wall
	cmp ah,0		; is ball moving left
	jne right_wall

	push 1
	call printnum

	mov byte [ball_x_dir],1	;flip
	mov byte [ball_x], 0		; place ball on left wall
	jmp end_ref_x_wall
right_wall:	
	push 2
	call printnum

	mov byte [ball_x_dir],0	;flip
	;; compute the size of ball
	xor ax,ax
	mov al,80		; right boundary
	xor bx,bx		; higher byte may contain garbage	
	mov bl,[ball_size]
	sub al,bl		
	mov byte [ball_x], al	; place ball on right wall

	xor ax,ax
	mov al,[ball_x]
	push ax
	call printnum
	
	jmp end_ref_x_wall
end_ref_x_wall:
	
	pop bx
	pop ax
	ret

ref_y_wall:
	;; get reflection in y-axis of wall
	;; just flips ball_x_dir
	;; no parameters given. it access global vars
	;; store states
	push ax			;store state
	push bx
	push dx
	
	mov ah,[ball_y_dir]
	;; if ball is moving up
	;; chage dir and set the ball on top wall
	;; cmp ah,0		; is ball moving up
	cmp ah,0		; is ball moving up
	jne red_zone		; ball is on last line

	push 3
	call printnum
	
	mov byte [ball_y_dir],1	; set ball dir downward
	mov byte [ball_y], 0		; place ball on top wall
	jmp end_ref_y_wall
red_zone:
	;; if ball is on the board
	push 4
	call printnum
	
	xor ax,ax
	mov al,[board_x]	; ax holds left loc of board
	xor bx,bx
	mov bl,[board_length]		; length of board
	add bx, ax		; right loc of board

	xor dx,dx
	mov dl,[ball_x]		; ball_x pos
	cmp dx,ax		; ball.x < board_left_corner ?
	jb game_out		;
	cmp dx,bx		; ball.x > board_right_corner ?
	ja game_out		;
	
	mov byte [ball_y_dir],0	; change y-dir up
	mov byte [ball_y], 24	; place ball just above the board
	jmp end_ref_y_wall
	
game_out:
	xor ax,ax
	mov al,[life]		; load lives
	dec ax
	mov [life],ax		; update life
	cmp ax,0
	jne play_again
	call end_of_game
	jmp end_ref_y_wall
play_again:
	;; call clearScreen
	;; call reset_game
	;; call start_game
	;; jmp end_of_game
	mov byte [ball_x],40	; reset ball pos
	mov byte [ball_y],24
	
	mov byte [game_out_flag], 1
end_ref_y_wall:	
	pop dx
	pop bx
	pop ax
	ret

bounce_on_brick:
	;; once brick is detected
	;; it determines direction of ball
	;; no parameter passed. it temperes global vars
	;; which at a time required by others subroutines
	;; it does not check whether given coordinate
	;; is a brick, it is callers responsibility
	push ax
	push bx
	push cx
	push dx

	xor ax,ax
	xor bx,bx
	xor cx,cx	
	xor dx,dx
		
	mov dh, [ball_x_dir]
	mov dl, [ball_y_dir]

	mov ah, [ball_x]
	mov al, [ball_y]
	
	cmp byte dl,0			; if ball moving up
	jne brick_is_below

	;; push ax			;store state
	sub al,1		; pos of ball vertically above
	push 0			; pass by ref
	push ax
	add al,1
	call brick_test
	pop ax
	cmp ax,0		;test vertically up space empty
	;; pop ax			;restore the state of ax
	je ref_x_axis
	jmp ref_y_axis
ref_x_axis:
	call ref_x_brick
	jmp end_bounce
ref_y_axis:
	call ref_y_brick
	jmp end_bounce
	
brick_is_below:
	
	add al,1
	push 0
	push ax
	sub al,1
	call brick_test
	pop ax
	cmp ax,0
	je ref_x_axis
	jmp ref_y_axis
end_bounce:
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
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

	
printnum:
	push bp
	mov bp,sp
	push es
	push ax
	push bx
	push cx
	push dx
	push di

	mov ax,0xb800
	mov es,ax
	mov ax,[bp+4]
	mov bx,10
	mov cx,0
nextdigit:
	mov dx,0
	div bx
	add dl,0x30
	push dx
	inc cx
	cmp ax,0
	jnz nextdigit

	mov di,1680
nextpos:
	pop dx
	mov dh,0x07
	mov [es:di],dx
	add di,2
	loop nextpos

	pop di
	pop dx
	pop cx
	pop bx
	pop ax
	pop es
	pop bp
	ret 2	


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
	push dx
	
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

	pop dx
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
	push bx
	push cx
	push dx
	
	;; on even line leave space on left
	xor ax,ax
	mov ax,[bp+6]		;
	mov bh,2
	div bh
	cmp ah,0
	je even_line
	mov cx,1		;left most col
	mov dx,1		; dx 1: even odd line
	jmp while_incomplete
even_line:
	mov cx,0		;left most col
	mov dx,0		; dx 0 means even line
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
	
	xor dx,0x1
	sub ax,dx
	
	push ax			;length
	mov ax,1
	push ax			;height of rectangle
	mov ax,[bp+4]		;fill color of rectangle
	push ax
	push cx			;cx holds the pos of left-top rectangle
	mov ax,[bp+6]		;line number as y pos
	push ax
	call draw_rectangle

	pop dx
	pop cx
	pop bx
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
	ret 
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
	xor ax,ax
	mov al,[board_length]
	push ax			;lenght of bounce board
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
	mov al,'o'
	;; 

	mov [es:di],ax
	;; add di,2
	;; mov [es:di],ax

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
	jmp cases_handled
y_pos:
	add bl,cl
cases_handled:	
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
	;; return 1 if brick found
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
	cmp byte al, 223		; is color black
	;; comparison could also be made by space character
	;; 	jne not_brick
	je brick_found
	add di,2
	mov ax,[es:di]
	cmp al, 223
	jne not_brick
	;; cmp byte ah, 0x00
	;; jne not_brick
brick_found:	
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

	
handle_refs:
	;; handle_refs(pos.xy)
	;; ball's next position is analysed
	;; and decided whether it collided
	;; with any boundary or not
	push ax
	push bx
	push cx
	push dx
	
	mov ax,[bp+4]		; ball's next pos
	;; x pos in higher byte
	cmp ah,79		; is ball in screen
	jae apply_x_ref
	cmp al,25
	jae apply_y_ref

	xor ax,ax
	xor bx,bx
	xor cx,cx
	xor dx,dx
	
	mov ah,[ball_x]	; load x pos
	mov al,[ball_y]	; load y pos
	mov ch,1	; speed of ball in x-dir
	mov cl,1	; speed of ball in y-dir
	mov dh,[ball_x_dir]	; positive or negative
	mov dl,[ball_y_dir]	; positive or negative
	
	;; compute next pos of ball
	push 0			;next-pos
	push ax			;current-pos
	push cx			;speed
	push dx			;direction
	call next_pos
	pop bx

	cmp bh,79
	jae apply_x_ref
	cmp bl,25
	jae apply_y_ref
	
	mov byte [ball_x], bh
	mov byte [ball_y], bl
	jmp end_boundray_ref
apply_x_ref:	
	;; push 101
	;; call printnum
	call ref_x_wall
	jmp end_boundray_ref
apply_y_ref:
	call ref_y_wall
end_boundray_ref:
	pop dx
	pop cx
	pop bx
	pop ax
	ret 2	

start_game:
	
	;; animation part	
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx

	;; 	call delay
;; 	call delay
;; 	push 0			;
;; 	push 0			; random direction
;; 	push 30			; generate random between 0 and 20
;; 	call random_in_range	; random for x-dir
;; 	pop ax
;; 	cmp ax, 10
;; 	ja rand_dir_neg
;; 	mov byte [ball_x_dir], 1
;; rand_dir_neg:
;; 	;; random direction is negative
;; 	mov byte [ball_x_dir], 0
	
while_not_over:
	xor ax,ax
	xor bx,bx
	xor cx,cx
	xor dx,dx

	
	mov al,[board_x]
	push ax
	call draw_bounce_board
	xor ax,ax
	
	mov ah,[ball_x]	; load x pos
	mov al,[ball_y]	; load y pos
	mov ch,1	; speed of ball in x-dir
	mov cl,1	; speed of ball in y-dir
	mov dh,[ball_x_dir]	; positive or negative
	mov dl,[ball_y_dir]	; positive or negative
	
	;; computer next pos of ball
	push 0			;next-pos
	push ax			;current-pos
	push cx			;speed
	push dx			;direction
	call next_pos
	pop bx

	;; if not brick, moveforward
	;; else bounce
	push 0			;
	push bx			; testing next pos
	call brick_test
	pop ax			; flag
	cmp ax,1		; 1:true
	je it_is_brick
	;; perform boundry test

	
	mov ah,[ball_x]		; refresh ax
	mov al,[ball_y]

	push bx
	call handle_refs	;handle reflections

	;; or brick, hence move forward
	
	jmp all_cases_handled

it_is_brick:
	
	mov ah,[ball_x]		; ball to draw
	mov al,[ball_y]		; load ball.xy before overwrite;
	call bounce_on_brick
	push bx
	call destroy_brick
	
all_cases_handled:
	;; push ax			;pos of ball
	;; push 40			;pos of board
	;; ;; call printnum
	;; call draw_ball_board

	;; push ax
	;; in al,0x60
	;; pop ax
	
	push 0x07		;white color
	mov bh,0x00			;
	mov bl,ah			;
	push bx			;x-pos of ball
	mov bh,0x00			;	
	mov bl,al		;y-pos of ball
	push bx
	call draw_ball

	call delay

	push ax
	mov ah, 0
 	int 0x16
	pop ax

	;; 	delete ball after delay
	push 0x00		;		black color same as screen background
	mov bh,0x00
	mov bl,ah			
	push bx			;			x-pos of ball
	mov bh,0x00				
	mov bl,al		;		y-pos of ball
	push bx
	call draw_ball

	mov ah,[life]
	cmp byte ah,0
	je exit_game
	jmp while_not_over
	
exit_game:
	
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
	call start_game

	
	;; xor bx,bx
	;; ;; call ref_x_wall
	;; mov bx,[ball_y]
	;; push bx
	;; call printnum
	
	;; xor ax, ax
	;; mov es, ax ; point es to IVT base

	;; mov ax,[es:9*4]
	;; mov [oldisr],ax
	;; mov ax,[es:9*4+2]
	;; mov [oldisr+2],ax
	
	;; cli ; disable interrupts
	;; mov word [es:9*4], kbisr; store offset at n*4
	;; mov [es:9*4+2], cs ; store segment at n*4+2
	;; sti ; enable interrupts




end_of_game:
	
	;; mov ax,[oldisr]
	;; mov bx,[oldisr+2]
	;; cli
	;; mov [es:9*4],ax
	;; mov [es:9*4+2],bx
	;; sti

	mov ax, 0x4c00
	int 0x21
