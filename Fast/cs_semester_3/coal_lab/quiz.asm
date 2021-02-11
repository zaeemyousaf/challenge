[org 0x0100]
 		jmp start

prevVal:	db	0
msg1:	db 'Sector#1$'
msg2:	db 'Sector#2$'
msg3:	db 'Sector#3$'
msg4:	db 'Sector#4$'
;============================================================ 		
; timer displaying subroutine
;============================================================ 		
printnum:	push bp
 			mov bp, sp
 			push es
 			pusha
 			mov ah,00	
			mov al,03h	
			int 10h
 			mov ax, 0xb800
 			mov es, ax 
 			mov ax, [bp+4]
 			mov bx, 10
 			mov cx, 0 
nextdigit:	mov dx, 0 
 			div bx 
 			add dl, 0x30
 			push dx 
 			inc cx 
 			cmp ax, 0 
 			jnz nextdigit
 			mov di, [bp+6]
			nextpos: pop dx 
			mov dh, 0x07 
			mov [es:di], dx 
			add di, 2 
			loop nextpos 
			popa
			pop es
			pop bp
			ret 2
;============================================================ 		
; timer interrupt service routine
;============================================================ 		
timer: 		push ax
			push ax
			mov dl, ah
GetVAl:		in al, 0x60
			cmp dl, al
			jne setter
continue:	mov al, 0x20
			cmp dl,	30
			je state1
			cmp dl,	48
			je state2
			cmp dl,	46
			je state3
			cmp dl,	32
			je state4
			cmp dl,1
			je exittimer
			jmp display
setter:		mov dl, al
			jmp continue
state1:		pop ax
			push 500
			mov cx, 0
			push msg1
			call SectorDis
			call delay
 			jmp display
state2:		pop ax
			push 620
			mov cx, 0
			push msg2
			call SectorDis
			call delay
 			jmp display
state3:		pop ax
			push 2900
			mov cx, 0
			push msg3
			call SectorDis
			call delay
			jmp display
state4:		pop ax
			push 3020
			mov cx, 0
			push msg4
			call SectorDis
			call delay
			jmp display

display:	add cx, 1
 			push cx
 			call delay
 			call printnum 
			jmp GetVAl

exittimer:	pop ax
			pop ax
 			iret 
;============================================================ 		
; display sector routine
;============================================================ 		
 SectorDis:	push bp
 			mov bp, sp
 			pusha
 			mov dx, [bp+4] 
 			mov ah, 9
 			int 0x21
 			popa
 			pop bp
 			ret 2
;============================================================ 		
; delay causing routine
;============================================================ 		
 delay:		pusha
 			mov cx, 0x8fff
ldelay:		sub cx, 1
 			cmp cx, 0
 			jne ldelay
 			popa
 			ret
;============================================================ 		
; Starting routine
;============================================================ 		 			
start: 		mov ah,00	
			mov al,03h	
			int 10h	
			push es 
			xor ax, ax
			mov es, ax 
			cli 
			push word [es:0x0*4]
			push word [es:0x0*4+2]
			mov word [es:0x0*4], timer
			mov [es:0x0*4+2], cs 
			sti  

			mov ah, 0
			int 0x16
			cmp al, 27
			je back

			int 0x0
			
back:		pop word [es:0x0*4+2]
			pop word [es:0x0*4]
			pop es

exit:		mov ax, 0x4c00
			int 0x21
