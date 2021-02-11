	;; add one line at 303 for status update
	;; add welcome screen
	;; detect game end
	;; random function has been overwritten by timer
	;; timer interrupt
	;; bug fix (handle refs: push bp)
     	;; l19-1196 BCS-3E
	;; Code of project phase-4
	;; in future I would use interrupt
	
[org 0x0100]
	jmp start

old_kbisr:	dd 0	
old_tmisr:	dd 0
	
ball_x:	db 40			; init x pos of ball
ball_y:	db 22			; just above the bounce board
board_x:	db 1		; in mid of screen; y is fixed
ball_x_dir:	db 1			; 0: left; 1:right
ball_y_dir:	db 0			; 0: up; 1:down
life:	db 3				; initial 3 life
ball_size:	db 1			; 2 char long
game_out_flag:	db 0			; out when 1
board_length:	db 20
score:	dw 0
game_status:	db 0		; initially not running
	;; pressing enter key, switches it on
	;; game_status:2 means that game is over
;;; -----------notifications
out_msg:	db 'L O S T',0
you_won:	db 'H U R R A H!  Y O U  W O N',0
life_msg:	db 'Life: ',0
score_msg:	db 'Score: ',0
time_msg:	db 'Elapsed time: ',0
milliseconds:	dw 0
seconds:	db 0		; time elapsed is in seconds
instructions:	db '<Enter key Start> <A: Left> <F: right>',0

any_brick_left:
	;; this functions chechs everytime
	;; whether game has ended or not
	;; is there any char other than deleted one
	;; between line 2 and line 10
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	

	xor ax,ax
	mov ax,0xb800
	mov es,ax
	xor di,di
	mov di,480		;2(3*80)
	xor bx,bx		; game is over
check_every_pixel:
	mov ax,[es:di]
	;; cmp ah,0x00		; is black color
	cmp byte al,' '		; is black color
	je check_next
	mov bx,1		; game not over
	jmp end_checking
check_next:
	add di,2		; visit next pixel
	cmp di, 1600		;
	jb check_every_pixel
end_checking:
	cmp bx,0		;
	je game_is_over
	jmp leave_routine
game_is_over:
	mov byte [game_status],2
leave_routine:

	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
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

	;; compute location
	push ax
	push bx
	
	mov ax,[bp+6]		;xy
	shl ax,8		; y is in lower byte (discarding higer part)
	shr ax,8		; higer part discarded
	mov bh,80
	mul bh			;80*y
	mov bx,[bp+6]		;xy
	shr bx,8			;x is in upper byte
	add ax,bx		;(80*y)+x
	shl ax,1			;2(80*y+x) actual position
	
	mov di,ax
	pop bx
	pop ax

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
	ret 4

ref_x_brick:

	;; get reflection in x-axis of brick	
	;; just flips ball_x_dir
	;; no parameters given. it access global vars
	;; store states
	push ax
	push bx	

	;; push 6
	;; call printnum
	
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

	;; push 5
	;; call printnum
	
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

	;; push 1
	;; call printnum

	mov byte [ball_x_dir],1	;flip
	mov byte [ball_x], 0		; place ball on left wall
	jmp end_ref_x_wall
right_wall:	
	;; push 2
	;; call printnum

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
	;; push ax
	;; call printnum
	
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
	push cx
	push dx
	
	mov ah,[ball_y_dir]
	;; if ball is moving up
	;; chage dir and set the ball on top wall
	;; cmp ah,0		; is ball moving up
	cmp ah,0		; is ball moving up
	jne red_zone		; ball is on last line

	;; push 3
	;; call printnum
	
	mov byte [ball_y_dir],1	; set ball dir downward
	mov byte [ball_y], 0		; place ball on top wall
	jmp end_ref_y_wall
red_zone:
	;; if ball is on board
	
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
	mov byte [ball_y], 23	; place ball just above the board
	jmp end_ref_y_wall
	
game_out:
	xor ax,ax
	mov al,[life]		; load lives
	dec ax
	cmp al,0
	jne play_again
	;; 	ja end_ref_y_wall
	jmp exit_game
play_again:	
	;; call clearScreen
	;; call reset_game
	;; call playisr
	;; jmp end_of_game
	cmp al,3
	ja exit_game
	mov byte [life],al
	mov byte [game_out_flag], 0
	;; correct direction
	mov byte [ball_y_dir],0
	;; reset game status
	mov byte [game_status],0 ; halt and wait for Enter key
	;; reset ball over the slider
	mov byte [ball_y],23
	mov byte [ball_x],45
	jmp end_ref_y_wall
exit_game:
	mov byte [life],0
	mov byte [game_out_flag], 1
	mov byte [game_status],2
end_ref_y_wall:
	pop dx
	pop cx
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
	mov cx,20
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
	push bx
	push cx
	push dx
	push es
	push di
	
	mov ax,0xb800
	mov es,ax
	mov ax,160		;one line has 80 pixels
	mov bx,[bp+4]
	sub bx,1		; line-1
	mul bx			; 80*(line_number-1)

	mov di,[bp+6]		;column
	;; 	sub di,1		; because real is zero based 
	shl di,1		;word-size
	add di,ax		; actual initial position of rectangle

	mov ax,[bp+8]		; fill color
	shl ax,8		; lower byte is empty
	mov al,223		
				;block is made up of blocks with color 		background
	;; mov ah,[bp+8]
	;; mov al,223		
	
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

	pop di
	pop es
	pop dx
	pop cx
	pop bx
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
	push es
	push di
;; 	;; on even line leave space on left
;; 	xor ax,ax
;; 	mov ax,[bp+6]		;
;; 	mov bh,2
;; 	div bh
;; 	cmp ah,0
;; 	je even_line
;; 	mov cx,0		;left most col
;; 	mov dx,4		; dx 1: even odd line
;; 	jmp while_incomplete
;; even_line:
;; 	mov cx,4		;left most col
;; 	mov dx,0		; dx 0 means even line
	mov cx,2
while_incomplete:
	mov ax,cx
	add ax,19		; 10 is max size of a brick
	cmp ax,80
	ja last_brick_remaining
	;; get random length on interval [5,10]
	call short_delay	; to bring randomness
	
	push 0			; random is stored her
	push 6
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

	sub ax,4		; creating gape from right
	cmp ax,0
	je zero_length
	
	push ax			;length
	mov ax,1
	push ax			;height of rectangle
	mov ax,[bp+4]		;fill color of rectangle
	push ax
	push cx			;cx holds the pos of left-top rectangle
	mov ax,[bp+6]		;line number as y pos
	push ax
	call draw_rectangle
zero_length:

	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 4

reset_game:
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	
	call clearScreen
	
	mov cx,0		; bricks starts from 
while:
	;; 	call delay
	
	mov ax,cx
	add ax,5		;1+topspace
	push ax		;first line number 1 not zero

	sub ax,4	;top space color correction
	sal ax,4	;make new color (works upto
	push ax
	;; 	add ax,4	;

	call draw_bricks_layer
	inc cx
	cmp cx,6		; has 4 lines been printed
	jb while

	;; draw ball over the board
	push 'o'		; shape char
	push 0x07		;white color same as screen background
	mov bh,0x00
	mov byte bl,[ball_x]			
	push bx			;-pos of ball
	mov bh,0x00				
	mov byte bl,[ball_y]		;y-pos of ball
	push bx
	call draw_ball
	;; set random ball dir
	push 0			; result
	xor ax,ax
	mov ax,0
	push ax			; min random
	mov ax,10
	push ax			; max random
	call random_in_range
	pop ax
	cmp byte al,5
	jb set_x_neg
	mov byte[ball_x_dir],1
	jmp end_of_set_x
set_x_neg:
	mov byte[ball_x_dir],0
	;; show life, score and timer
end_of_set_x:	
	;; call display_life	
	;; call display_score	;
	;; call display_time
	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	ret
	
draw_bounce_board:
	;; (color,xloc)
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	
	;; pass argument to draw_rectangle
	xor ax,ax
	mov al,[board_length]
	push ax			;lenght of bounce board
	push 1			;height
	mov ax,[bp+6]
	push ax		;color
	mov ax,[bp+4]		;x-pos
	push ax
	push 25		;y-pos, last row
	call draw_rectangle

	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 4

draw_ball:
	;; [shape_char,color,x,y,call,bp
	;; draw the ball
	;; and clear the ball as well
	;; by repainting
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
	mov ax,160
	mov bx,[bp+4]		;y-pos
	mul bx			;160*y
	mov bx,[bp+6]		;x-pos
	shl bx,1
	add ax,bx		;160*y+x
	mov di,0		;points to left-top
	add di,ax		;the actual pos of ball

	mov ax,[bp+10]		;shape char will be in lower byte
	mov ah,[bp+8]		; color
	;; mov al,'o'
	;; 

	mov [es:di],ax
	;; add di,2
	;; mov [es:di],ax

	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 8

next_pos:
	;; [0,ax,cx,dx,call,bp
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	
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

	pop di
	pop es
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

	mov di,ax
	mov cx,di		;
	add cx,2		;this side will be cleared by delete_right

delete_left:
	xor ax,ax
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
	pop di
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
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	
	mov ax,[bp+4]		; ball's next pos
	;; x pos in higher byte
	cmp byte ah,79		; is ball in screen
	jae apply_x_ref
	cmp byte al,24
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
	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret 2	

playisr:
	;; play timer interrupt routine
	;; it moves the ball one step forward
	;; and handles all sort of reflections
	;; animation par
	push ax
	push bx
	push cx
	push dx

	xor ax,ax
	mov al,[seconds]
	inc ax
	mov byte [seconds],al

	
	;; check game status
	mov byte al,[game_status]
	cmp al,0
	je game_not_started
	;; while_not_over
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

	cmp byte al,23
	jne add_score
	jmp all_cases_handled
add_score:
	push ax
	xor ax,ax
	mov ax,[score]
	add ax,5		;score factor
	mov [score],ax
	pop ax
	
all_cases_handled:

	;; avoid destroying slider
	;; clear ball previously drawn
	push bx			;store state

	push ' '		; empty char
	push 0x00		; black color
	mov bh,0x00			;
	mov bl,ah			;
	push bx			;x-pos of ball
	mov bh,0x00			;	
	mov bl,al		;y-pos of ball
	push bx
	call draw_ball
	pop bx
	;; 	draw at new location
	cmp byte bl,20
	ja it_is_slider
	push bx
	call destroy_brick
	
it_is_slider:	

	push 'o'
	push 0x07		;white color same as screen background
	mov bh,0x00
	mov byte bl,[ball_x]			
	push bx			;-pos of ball
	mov bh,0x00				
	mov byte bl,[ball_y]		;y-pos of ball
	push bx
	call draw_ball
game_not_started:
	;; game may or may not have started here
	xor ax,ax
	mov al,[game_status]
	cmp al,1		;not started
	je has_started
	call display_welcome
	jmp not_started
has_started:
	call clear_welcome
not_started:	
	mov al,0x20
	out 0x20,al

	pop dx
	pop cx
	pop bx
	pop ax

	iret
	;; 	ret

move_slider_isr:
	;; kbd int service routine
	;; it moves one slider one step forward
	;; read and go either left or right
	;; move slider key board interrupt
	push ax
	push bx
	push cx
	push dx
	
	xor bx,bx
	mov bl,[board_x]	; store old loc of slider
	;; clear old drawn slider	

	in al, 0x60
	cmp al, 33
	je right_shift
	;; left shift was pressed
	cmp al,30
	je left_shift
	cmp al,27
	je quit_game
	jmp no_quit
quit_game:
	mov byte[game_out_flag],1
	mov byte[game_status],2
	;; mov byte[life],0
no_quit:	
	;; set game_out flag
	push ax			;store state
	xor ax,ax
	mov al,1
	mov byte [game_out_flag],al
	pop ax

	cmp al,28		;is Enter key pressed
	je init_game
	jmp end_kb_isr

init_game:
	mov byte [game_status],1
left_shift:
	xor ax,ax
	mov al,[board_x]
	sub ax,2
	mov byte [board_x],al
	jmp no_match_key

right_shift:
	xor ax,ax
	mov al,80
	sub al,[board_length]
	push bx			; store
	mov bl,[board_x]
	add bl,4
	cmp bl,al
	pop bx			;restore
	ja no_match_key
	xor ax,ax
	mov al,[board_x]
	add ax,4
	mov byte [board_x],al

no_match_key:
	mov byte bl,[board_x]
	cmp byte bl,80		;has slider become negative
	ja place_on_left
	xor ax,ax
	mov ax,80
	sub al,[board_length]
	cmp bl,al		;
	ja place_on_right	;
	;; else movement is valid
	jmp end_kb_isr
	
place_on_left:
	mov byte [board_x],0
	jmp end_kb_isr
place_on_right:
	xor ax,ax
	mov al,80
	sub al,[board_length]
	mov byte[board_x],al
	;; push ax
	;; call printnum
	jmp end_kb_isr
	
end_kb_isr:
	;; clear old pos
	mov ah,bl
	add ah,1
	mov al,24
	cmp bl,80
	ja no_clear		; do not clear slider when on left most
	
	push ax
	call destroy_brick
no_clear:
	
	xor ax,ax
	mov al,0x07
	push ax
	xor ax,ax
	mov al,bl	; bx holds old pos of slider
	push ax			;old value
	call draw_bounce_board
	xor ax,ax
	
	mov al,0x20
	out 0x20,al

	pop dx
	pop cx
	pop bx
	pop ax
	
	iret			;


hook_kbisr:
	;; it hooks kbd int service routine
	push ax
	push bx
	push cx
	push dx

	
	xor ax, ax
	mov es, ax ; point es to IVT base

	mov ax,[es:9*4]
	mov [old_kbisr],ax
	mov ax,[es:9*4+2]
	mov [old_kbisr+2],ax
	
	cli ; disable interrupts
	mov word [es:9*4], move_slider_isr; store offset at n*4
	mov [es:9*4+2], cs ; store segment at n*4+2
	sti ; enable interrupts


	pop dx
	pop cx
	pop bx
	pop ax
	ret

hook_tmisr:
	;; it hooks kbd int service routine
	push ax
	push bx
	push cx
	push dx
	
	;; timer interrupt
	xor ax, ax
	mov es, ax ; point es to IVT base

	mov ax,[es:8*4]
	mov [old_tmisr],ax
	mov ax,[es:8*4+2]
	mov [old_tmisr+2],ax
	
	cli ; disable interrupts
	mov word [es:8*4], playisr; store offset at n*4
	mov [es:8*4+2], cs ; store segment at n*4+2
	sti ; enable interrupts

	pop dx
	pop cx
	pop bx
	pop ax
	ret

unhook_kbisr:
	;; it unhooks kbd int service routine
	push ax
	push bx
	push cx
	push dx

	
	xor ax,ax
	mov es,ax
	
	mov ax,[old_kbisr]	
	mov bx,[old_kbisr+2]

	mov [es:9*4],ax
	mov [es:9*4+2],bx

	pop dx
	pop cx
	pop bx
	pop ax
	ret

unhook_tmisr:
	;; it unhooks kbd int service routine
	push ax
	push bx
	push cx
	push dx

	;; ;; unhooking timer interrupt
	xor ax, ax
	xor bx,bx
	mov es, ax ; point es to IVT base

	mov ax,[old_tmisr]	
	mov bx,[old_tmisr+2]

	mov [es:8*4],ax
	mov [es:8*4+2],bx

	pop dx
	pop cx
	pop bx
	pop ax
	ret

display_life:
	;; it reads life from global variable
	;; display label first
	push ax
	push bx
	push cx
	push dx

	mov ax,1		; x pos left most top
	push ax
	mov ax,1
	push ax			; left corner

	mov ax,2
	push ax
	mov ax, life_msg
	push ax
	call printstr
	;; ;; value

	push 0x0701		;col: 7 row:0
	xor ax,ax
	mov al,[life]
	push ax
	call printnum

	
	pop dx
	pop cx
	pop bx
	pop ax
	ret

display_welcome:
	;; it reads life from global variable
	;; display label first
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	
	mov ax,20		; x pos left most top
	push ax
	mov ax,16
	push ax			; left corner

	mov ax,6
	push ax
	mov ax, instructions	;
	push ax
	call printstr
	

	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	ret
clear_welcome:
	;; it reads life from global variable
	;; display label first
	push ax
	push bx
	push cx
	push dx
	push es
	push di
	
	mov ax,20		; x pos left most top
	push ax
	mov ax,16
	push ax			; left corner

	mov ax,0x00
	push ax
	mov ax, instructions	;
	push ax
	call printstr
	

	pop di
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	ret

display_score:
	;; it reads score from global variable
	;; display label first
	push ax
	push bx
	push cx
	push dx

	mov ax,30		; x pos center
	push ax
	mov ax,1
	push ax			; top row

	mov ax,2
	push ax
	mov ax, score_msg
	push ax
	call printstr
	
	push 0x2501		;col: 7 row:0
	xor ax,ax
	mov ax,[score]
	push ax
	call printnum
	
	pop dx
	pop cx
	pop bx
	pop ax
	ret

display_time:
	;; it reads time from global variable
	;; display label first
	push ax
	push bx
	push cx
	push dx

	mov ax,60		; x pos center
	push ax
	mov ax,1
	push ax			; top row

	mov ax,2		;color
	push ax
	mov ax, time_msg
	push ax
	call printstr

	xor ax,ax
	mov al,[game_status]
	cmp al,0
	je game_not_running
	
	push 0x4901
	xor ax,ax
	mov ax,[milliseconds]
	inc ax
	mov [milliseconds],ax

	sub ax,1
	mov bl,18		;18.18...
	xor dx,dx
	div bl
	mov byte [seconds],al	;store the quetient
	mov ah,0
	push ax
	call printnum
game_not_running:	
	pop dx
	pop cx
	pop bx
	pop ax
	ret

display_out:
	;; on exit, game status is analysed
	;; and concluded whether win or lost
	push ax
	push bx
	push cx
	push dx

	call clearScreen
	mov ax,40		; x pos center
	push ax
	mov ax,12
	push ax			; top row

	mov ax,4		; red color color
	push ax
	mov ax, out_msg
	push ax
	call printstr
	
	pop dx
	pop cx
	pop bx
	pop ax
	ret

display_win:
	;; on exit, game status is analysed
	;; and concluded whether win or lost
	push ax
	push bx
	push cx
	push dx

	mov ax,40		; x pos center
	push ax
	mov ax,12
	push ax			; top row

	mov ax,2		;color
	push ax
	mov ax, you_won
	push ax
	call printstr
		
	pop dx
	pop cx
	pop bx
	pop ax
	ret

printstr:
	;; this code taken from book is not commented pg. 113
	push bp
	mov bp,sp
	push es
	push ax
	push cx
	push si
	push di

	push ds
	pop es
	mov di, [bp+4]
	mov cx,0xffff
	xor al,al
	repne scasb
	mov ax, 0xffff
	sub ax,cx
	dec ax
	jz exit

	mov cx,ax
	mov ax,0xb800
	mov es,ax
	mov al,80
	mul byte [bp+8]
	add ax,[bp+10]
	shl ax,1
	mov di,ax
	mov si,[bp+4]
	mov ah,[bp+6]

	cld
nextchar:
	lodsb
	stosw
	loop nextchar
exit:
	pop di
	pop si
	pop cx
	pop ax
	pop es
	pop bp
	ret 8

;;; =============================== main		
start:
	call reset_game
	call display_welcome

	
	call hook_kbisr		; hook kbd int service rountine
	call hook_tmisr		;hook timer int service routine


my_loop:
	call display_life	
	call display_score	;
	call display_time

	call delay

	call any_brick_left
	
	xor ax,ax
	mov byte al,[game_status]
	cmp al,2
	je unhook_and_exit
	jmp my_loop
	

unhook_and_exit:	
	;; --------------------
	;; unhook kbd interrupt
	;; terminate with residing here
	call unhook_kbisr
	call unhook_tmisr

	;; --------------------
	;; game is over now
	call display_life	
	call display_score	;
	call display_time

	xor ax,ax
	mov al,[life]
	cmp al,0
	je display_out_msg
	call display_win
	jmp bye
display_out_msg:
	call display_out
bye:	

	mov ax, 0x4c00
	int 0x21
