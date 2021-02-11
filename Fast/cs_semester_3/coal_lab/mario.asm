[org 0x100]


jmp start

marioPos:	dw 0
tickcount:		dw 0
status:		db 0;		0 for stationery,1 for up and 2 for down
limitOfJump:	db 0
enemy1:		dw 0
enemy2:		dw 0
enemiesStatus:	db 0
gameStatus:	db 0
oldtimer:		dw 0
monster:		dw 0
monsterStatus:	db 0
monsterBall:	dw 0
ballStatus: 	db 0

drawRectangle:	push bp		;parameters:	attributes,coordinates,heightxlength
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov ah,02	;move cursor to coordinates
		mov bh,0
		mov dx,[bp+6]
		int 10H
		mov cx,[bp+8]
		mov al,cl
		mov bl,ch
		mov cx,[bp+4]
		mov di,cx		;set height and length
		mov ch,0
		push ax
		mov ax,di
		mov al,ah
		mov ah,0
		mov di,ax
		pop ax
		mov si,0

l1:		mov ah,09h
		int 10h
		add dh,1
		mov bh,0
		mov ah,02
		int 10h
		add si,1
		cmp si,di
		jnz l1

		pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 6

;_______________________________________________________________________

drawMario:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds
		
		mov dx,[marioPos]

		mov ah,00100000b;	                            draw face
		mov al,0x20
		push ax
		push dx
		push 0203h
		call drawRectangle
		
		mov ah,00100111b;	                            draw left eye
		mov al,0x2E
		push ax
		push dx
		push 0101h
		call drawRectangle

		mov ah,00100111b;	                            draw right eye
		mov al,0x2E
		push ax
		add dl,2
		push dx
		push 0101h
		call drawRectangle

		mov ah,00100111b;	                            draw nose
		mov al,0x3B
		push ax
		sub dl,1
		add dh,1
		push dx
		push 0101h
		call drawRectangle

		mov ah,01110111b;	                            draw neck
		mov al,0x20
		push ax
		add dh,1
		push dx
		push 0101h
		call drawRectangle

		mov ah,00010111b;	                            draw tummy
		mov al,0x20
		push ax
		add dh,1
		sub dl,2
		push dx
		push 0305h
		call drawRectangle

		mov ah,01110111b;	                            draw left leg
		mov al,0x20
		push ax
		add dh,3
		add dl,1
		push dx
		push 0101h
		call drawRectangle

		mov ah,01110111b;	                            draw right leg
		mov al,0x20
		push ax
		add dl,2
		push dx
		push 0101h
		call drawRectangle

		mov ah,01110111b;	                            draw left bicep
		mov al,0x20
		push ax
		sub dh,3
		sub dl,4
		push dx
		push 0101h
		call drawRectangle
		
		mov ah,01110111b;	                            draw left arm
		mov al,0x20
		push ax
		sub dl,1
		push dx
		push 0201h
		call drawRectangle

		mov ah,01110111b;	                            draw right bicep
		mov al,0x20
		push ax
		add dl,7
		push dx
		push 0101h
		call drawRectangle
		
		mov ah,01110111b;	                            draw right arm
		mov al,0x20
		push ax
		add dl,1
		push dx
		push 0201h
		call drawRectangle

		mov ah,02
		mov bh,0
		mov dh,60
		mov dl,00
		int 10H



		pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________

clearMario:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds
		
		mov word dx,[marioPos]

		mov ah,00000000b;	                            draw face
		mov al,0x20
		push ax
		push dx
		push 0203h
		call drawRectangle
		
		mov ah,00000000b;	                            draw left eye
		mov al,0x2E
		push ax
		push dx
		push 0101h
		call drawRectangle

		mov ah,00000000b;	                            draw right eye
		mov al,0x2E
		push ax
		add dl,2
		push dx
		push 0101h
		call drawRectangle

		mov ah,00000000b;	                            draw nose
		mov al,0x3B
		push ax
		sub dl,1
		add dh,1
		push dx
		push 0101h
		call drawRectangle

		mov ah,00000000b;	                            draw neck
		mov al,0x20
		push ax
		add dh,1
		push dx
		push 0101h
		call drawRectangle

		mov ah,00000000b;	                            draw tummy
		mov al,0x20
		push ax
		add dh,1
		sub dl,2
		push dx
		push 0305h
		call drawRectangle

		mov ah,00000000b;	                            draw left leg
		mov al,0x20
		push ax
		add dh,3
		add dl,1
		push dx
		push 0101h
		call drawRectangle

		mov ah,00000000b;	                            draw right leg
		mov al,0x20
		push ax
		add dl,2
		push dx
		push 0101h
		call drawRectangle

		mov ah,00000000b;	                            draw left bicep
		mov al,0x20
		push ax
		sub dh,3
		sub dl,4
		push dx
		push 0101h
		call drawRectangle
		
		mov ah,00000000b;	                            draw left arm
		mov al,0x20
		push ax
		sub dl,1
		push dx
		push 0201h
		call drawRectangle

		mov ah,00000000b;	                            draw right bicep
		mov al,0x20
		push ax
		add dl,7
		push dx
		push 0101h
		call drawRectangle
		
		mov ah,00000000b;	                            draw right arm
		mov al,0x20
		push ax
		add dl,1
		push dx
		push 0201h
		call drawRectangle

		mov ah,02
		mov bh,0
		mov dh,60
		mov dl,00
		int 10H



		pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________
drawHurdles:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov ah,01000000b; draw first hurdle leg
		mov al,0x20
		push ax
		mov ah,23
		mov al,13
		push ax
		mov ah,2
		mov al,3
		push ax
		call drawRectangle

		mov ah,01000000b; draw first hurdle head
		mov al,0x20
		push ax
		mov ah,22
		mov al,12
		push ax
		mov ah,1
		mov al,5
		push ax
		call drawRectangle

		mov ah,01000000b; draw second hurdle leg
		mov al,0x20
		push ax
		mov ah,22
		mov al,33
		push ax
		mov ah,3
		mov al,2
		push ax
		call drawRectangle

		mov ah,01000000b; draw second hurdle head
		mov al,0x20
		push ax
		mov ah,21
		mov al,32
		push ax
		mov ah,1
		mov al,4
		push ax
		call drawRectangle

		mov ah,01000000b; draw third hurdle leg
		mov al,0x20
		push ax
		mov ah,21
		mov al,55
		push ax
		mov ah,4
		mov al,3
		push ax
		call drawRectangle

		mov ah,01000000b; draw third hurdle head
		mov al,0x20
		push ax
		mov ah,20
		mov al,54
		push ax
		mov ah,1
		mov al,5
		push ax
		call drawRectangle

		
		mov ah,02;		          mov cursor to avoid input
		mov bh,0
		mov dh,60
		mov dl,00
		int 10H

		pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________

clearScreen:	push bp
		mov bp,sp
		push di
 		push ax

  		mov ax,0xb800
		mov es,ax
nextchar:		cmp di,4000
		je remChar
		mov ah,00000000b
		mov al,0x20
		mov word [es:di],ax
		add di,2
		jmp nextchar

remChar:		pop ax
		pop di
		pop bp
		ret

;_______________________________________________________________________

drawFlag:		push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov ah,00100000b; draw flag
		mov al,0x20
		push ax
		mov ah,01
		mov al,68
		push ax
		push 0308h
		call drawRectangle

		mov ah,01110000b; draw rod
		mov al,0x20
		push ax
		mov ah,01
		mov al,77
		push ax
		mov ah,24
		mov al,1
		push ax
		call drawRectangle

		mov ah,00100001b; draw patterns
		mov al,0x2A
		push ax
		mov ah,01
		mov al,70
		push ax
		mov ah,3
		mov al,3
		push ax
		call drawRectangle
		
		pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________
moveUp:		push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds
		
		
		mov word dx,[marioPos]
		cmp byte dh,[limitOfJump]
		jne upYes
		mov cl,2
		mov [status],cl
		jmp moveUpRet

upYes:		call clearMario
		call drawKingdom
		sub dh,1
		mov word [marioPos],dx
		call drawMario		 
		
moveUpRet:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret
;_______________________________________________________________________
moveDown:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov word dx,[marioPos]

onGround:	cmp dh,18
		jne onFirstHurdle
		mov cl,0
		mov [status],cl
		jmp moveDownRet
		
onFirstHurdle:	cmp dh,15
		jne onSecondHurdle
		cmp dl,06
		jng onSecondHurdle
		cmp dl,20
		jnl onSecondHurdle
		mov cl,0
		mov [status],cl
		jmp moveDownRet

onSecondHurdle:	cmp dh,14
		jne onThirdHurdle
		cmp dl,26
		jng onThirdHurdle
		cmp dl,39
		jnl onThirdHurdle
		mov cl,0
		mov [status],cl
		jmp moveDownRet

onThirdHurdle:	cmp dh,13
		jne downYes
		cmp dl,48
		jng downYes
		cmp dl,62
		jnl downYes
		mov cl,0
		mov [status],cl
		jmp moveDownRet

downYes:		call clearMario
		call drawKingdom
		add dh,1
		mov word [marioPos],dx
		call drawMario		 

moveDownRet:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________
kbisr:		push ax
 		push es

		mov cl,[gameStatus]
		cmp cl,1
		je kbisrRet
 		in al, 0x60 ; read a char from keyboard port
		mov word dx,[marioPos]

cond1:		cmp al,0x4D
		jne cond2
		cmp dl,74
		je kbisrRet

		cmp dl,06
		jne r_hurdle2
		cmp dh,15
		jl movRight
		jmp kbisrRet 
r_hurdle2:		cmp dl,26
		jne r_hurdle3
		cmp dh,14
		jl movRight
		jmp kbisrRet
r_hurdle3:		cmp dl,48
		jne movRight
		cmp dh,13
		jl movRight
		jmp kbisrRet
movRight:		call clearMario
		call drawKingdom
		add dl,01
		mov word [marioPos],dx
		call drawMario
		jmp kbisrRet

kbisrRet:		mov al, 0x20
		out 0x20, al ; send EOI to PIC
		pop es
		pop ax
		iret

cond2:		cmp al,0x4B
		jne cond3
		cmp dl,03
		je kbisrRet

		cmp dl,20
		jne l_hurdle2
		cmp dh,15
		jl movLeft
		jmp kbisrRet

l_hurdle2:		cmp dl,39
		jne l_hurdle3
		cmp dh,14
		jl movLeft
		jmp kbisrRet

l_hurdle3:		cmp dl,62
		jne movLeft
		cmp dh,13
		jl movLeft
		jmp kbisrRet


movLeft:		call clearMario
		call drawKingdom
		sub dl,01
		mov word [marioPos],dx
		call drawMario
		jmp kbisrRet

cond3:		cmp al,0x48
		jne kbisrRet
		mov cl,[status]
		cmp cl,2
		je kbisrRet
		cmp cl,1
		je kbisrRet
		sub dh,7
		mov [limitOfJump],dh
		mov cl,1
		mov [status],cl
		
		jmp kbisrRet		
;_______________________________________________________________________
drawEnemy1:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds
		
		mov dx,[enemy1]
		
		mov ah,01100000b;	                            draw face
		mov al,0x20
		push ax
		push dx
		push 0101h
		call drawRectangle

		sub dl,1
		add dh,1
		mov ah,01100000b;	                            draw lower
		mov al,0x20
		push ax
		push dx
		push 0103h
		call drawRectangle


drawEnemy1Ret:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________

clearEnemy1:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds
		
		mov dx,[enemy1]
		
		mov ah,00000000b;	                            clear face
		mov al,0x20
		push ax
		push dx
		push 0101h
		call drawRectangle

		sub dl,1
		add dh,1
		mov ah,00000000b;	                            clear lower
		mov al,0x20
		push ax
		push dx
		push 0103h
		call drawRectangle


clearEnemy1Ret:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________

drawEnemy2:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds
		
		mov dx,[enemy2]
		
		mov ah,01100000b;	                            draw face
		mov al,0x20
		push ax
		push dx
		push 0101h
		call drawRectangle

		sub dl,1
		add dh,1
		mov ah,01100000b;	                            draw lower
		mov al,0x20
		push ax
		push dx
		push 0103h
		call drawRectangle


drawEnemy2Ret:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 

;_______________________________________________________________________

clearEnemy2:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds
		
		mov dx,[enemy2]
		
		mov ah,00000000b;	                            clear face
		mov al,0x20
		push ax
		push dx
		push 0101h
		call drawRectangle

		sub dl,1
		add dh,1
		mov ah,00000000b;	                            clear lower
		mov al,0x20
		push ax
		push dx
		push 0103h
		call drawRectangle


clearEnemy2Ret:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret
;_______________________________________________________________________
drawMonster:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov bx,[monster]

		mov ah,01000000b;	                            draw upper of monster
		mov al,0x20
		push ax
		push bx
		push 0107h
		call drawRectangle
		
		add bh,1
		mov ah,00010000b;	                            draw upper of monster
		mov al,0x20
		push ax
		push bx
		push 0207h
		call drawRectangle

		add bh,2
		mov ah,00010000b;	                            draw face of monster
		mov al,0x20
		push ax
		add bl,3
		push bx
		push 0101h
		call drawRectangle

		add bh,1
		mov ah,0000100b;	                            draw nozzle of gun
		mov al,0x21
		push ax
		push bx
		push 0101h
		call drawRectangle
		
		mov cl,[ballStatus]
		cmp cl,0
		jne drawMonsterRet
		add bh,1
		mov ah,0000100b;	                            
		mov al,0x7C
		mov [monsterBall],bx
		push ax
		push bx
		push 0101h
		call drawRectangle
		mov cl,1
		mov [ballStatus],cl

drawMonsterRet:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret

;_______________________________________________________________________		
		
;_______________________________________________________________________
timer:		push ax; 			userdefined timer
		push bx
		push cx
		push dx

		mov dl,[gameStatus]

		cmp dl,1
		je timer_Ret
		inc word [cs:tickcount]
		
		call drawHurdles

drawBall:		mov cl,[ballStatus]
		mov bx,[monsterBall]
		cmp bh,25
		jne createBall
		mov cl,0
		mov [ballStatus],cl

createBall:	mov ah,0000000b;	                            clear ball
		mov al,0x20
		push ax
		push bx
		push 0101h
		call drawRectangle

		add bh,1
		mov [monsterBall],bx
		mov ah,0000010b;	                            clear ball
		mov al,0x7C
		push ax
		push bx
		push 0101h
		call drawRectangle
 

moveMonster:	mov ax,[monster]
		cmp al,55
		jne monR
		mov cl,0
		mov [monsterStatus],cl
		jmp createMonster

monR:		cmp al,0
		jne createMonster
		mov cl,1
		mov [monsterStatus],cl
		jmp createMonster
timer_Ret:	jmp timerRet

createMonster:	mov cl,[monsterStatus]
		mov dh,00000000b;	                            draw upper of monster
		mov dl,0x20
		push dx
		push 0000h
		push 0655h
		call drawRectangle

		cmp cl,1
		jne nConM
		add al,1
		mov byte [monster],al
		call drawMonster
		jmp moveEnemies

nConM:		sub al,1
		mov byte [monster],al
		call drawMonster
		jmp moveEnemies
;				
;
		
moveEnemies:	mov ax,[tickcount]
		mov bx,3
		mov dx,0
		div bx		
		cmp dx,0
		jne moveMario

		mov ax,[enemy1]
		mov bx,[enemy2]

		cmp al,17
		jne Eleft
		mov cl,1
		mov [enemiesStatus],cl
		jmp Enext


Eleft:		cmp al,28
		jne Enext
		mov cl,0
		mov [enemiesStatus],cl

Enext:		mov cl,[enemiesStatus]
		cmp cl,1
		jne movEL
		call clearEnemy1
		call clearEnemy2
		add al,1
		add bl,1
		mov [enemy1],ax
		mov [enemy2],bx
		call drawEnemy1
		call drawEnemy2
		jmp moveMario

movEL:		call clearEnemy1
		call clearEnemy2
		sub al,1
		sub bl,1
		mov [enemy1],ax
		mov [enemy2],bx
		call drawEnemy1
		call drawEnemy2
		jmp moveMario


moveMario:	mov ax,[tickcount]
		mov bx,2
		mov dx,0
		div bx		
		cmp dx,0
		jne timerRet

		mov cl,[status]
		cmp cl,1
		jne md
		call moveUp

md:		mov cl,[status]
		cmp cl,1
		je timerRet
		call moveDown

		

timerRet:		call youLost
		call youWon
		mov al,0x20
		out 0x20,al

		pop dx
		pop bx
		pop cx
		pop ax
		iret
;_______________________________________________________________________
youLost:		push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov bx,[monsterBall]
		mov ax,[marioPos]
		cmp bh,ah
		jle collideCheck
		sub al,3
		cmp bl,al
		jl collideCheck
		add al,8
		cmp bl,al
		jg collideCheck
		add ah,6
		cmp bh,ah
		jge collideCheck
		jmp printLost

collideCheck:	mov ax,[marioPos]
		mov bx,[enemy1]
		mov cx,[enemy2]

		cmp ah,17
		jl youLost_Ret
		
		mov ah,al
		add al,2

		mov bh,bl
		add bl,2
		sub bh,1
		;add bl,1

		mov ch,cl
		add cl,2
		sub cl,1
		sub ch,1

enemy1Collide:	cmp ah,bh		;leftLegCollideWithEnemy1
		jne m1LR
		jmp printLost
		
m1LR:		cmp ah,bl
		jne m1RL
		jmp printLost

m1RL:		cmp al,bh
		jne m1RR
		jmp printLost

m1RR:		cmp al,bl
		jne enemy2Collide
		jmp printLost

youLost_Ret:	jmp youLostRet

enemy2Collide:	cmp ah,ch		;leftLegCollideWithEnemy1
		jne m2LR
		jmp printLost
		
m2LR:		cmp ah,cl
		jne m2RL
		jmp printLost

m2RL:		cmp al,ch
		jne m2RR
		jmp printLost

m2RR:		cmp al,cl
		jne youLostRet
		jmp printLost

printLost: 		mov cl,1
		mov [gameStatus],cl
		call clearScreen
		mov ah,00000010b
		mov al,'L'
		push ax
		mov ah,12
		mov al,38
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle

		mov ah,00000010b
		mov al,'O'
		push ax
		mov ah,12
		mov al,39
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle

		mov ah,00000010b;	
		mov al,'S'
		push ax
		mov ah,12
		mov al,40
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle
		
		mov ah,00000010b;	screenclear
		mov al,'T'
		push ax
		mov ah,12
		mov al,41
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle		

youLostRet:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret		
;_______________________________________________________________________
youWon:		push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov word dx,[marioPos]
		cmp dl,74
		jne youWonRet
		
	
printWon:		mov cl,1
		mov [gameStatus],cl
		call clearScreen
		mov ah,00000010b
		mov al,'W'
		push ax
		mov ah,12
		mov al,38
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle

		mov ah,00000010b
		mov al,'O'
		push ax
		mov ah,12
		mov al,39
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle

		mov ah,00000010b;	
		mov al,'N'
		push ax
		mov ah,12
		mov al,40
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle
				

youWonRet:	pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret
;_______________________________________________________________________
drawKingdom:	push bp		
		mov bp,sp
		push ax
		push bx
		push cx
		push dx
		push si
		push di
		push es
		push ds

		mov ah,01001000b;	                            draw ground storey
		mov al,0x20
		push ax
		mov ah,23
		mov al,70
		push ax
		mov ah,02
		mov al,10
		push ax
		call drawRectangle

		mov ah,01001000b;	                            draw middle storey
		mov al,0x20
		push ax
		mov ah,21
		mov al,71
		push ax
		mov ah,02
		mov al,8
		push ax
		call drawRectangle
		
		mov ah,01001000b;	                            draw door
		mov al,0x20
		push ax
		mov ah,19
		mov al,73
		push ax
		mov ah,02
		mov al,4
		push ax
		call drawRectangle
	
		mov ah,00011000b;	                            draw upper storey
		mov al,0x20
		push ax
		mov ah,22
		mov al,73
		push ax
		mov ah,03
		mov al,4
		push ax
		call drawRectangle

		mov ah,01110000b;	                            draw upper storey
		mov al,0x2E
		push ax
		mov ah,23
		mov al,73
		push ax
		mov ah,01
		mov al,01
		push ax
		call drawRectangle
	
		pop ds
		pop es
		pop di
		pop si
		pop dx
		pop cx
		pop bx
		pop ax
		pop bp
		ret 


;_______________________________________________________________________

start:		mov ah,00000000b;	screenclear
		mov al,0x20
		push ax
		mov ah,00
		mov al,00
		push ax
		mov ah,25
		mov al,80
		push ax
		call drawRectangle
		call drawKingdom

		mov ah,18
		mov al,03
		mov word [marioPos],ax
		call drawMario
		call drawHurdles
		
		mov ah,23
		mov al,20
		mov word [enemy1],ax
		call drawEnemy1
		
		mov ah,23
		mov al,45
		mov word [enemy2],ax
		call drawEnemy2		

		mov ah,00
		mov al,25
		mov word [monster],ax
		call drawMonster

		xor ax, ax;			keyboard interrupt hooking
		mov es, ax ;
		cli ; 
		mov word [es:9*4], kbisr ; 
		mov [es:9*4+2], cs ; 
		sti
	
		xor ax,ax;			hooking interrupt 8(timer)
		mov es,ax
		cli
		mov word [es:8*4],timer
		mov [es:8*4+2],cs
		sti

loo:		jmp loo

end:		mov ax,0x4c00
		int 0x21
