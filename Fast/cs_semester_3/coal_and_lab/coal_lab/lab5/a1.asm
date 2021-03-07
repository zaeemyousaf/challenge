; SomeFunction with Global Variables
[ORG 0x0100]
jmp start
a: 		db 0xA
b: 		db 0xB
c: 		db 0xC
min:	db 0xF
max:	db 0x0
total:	db 0x0
avg:	db 0x0
ans:	db 0x0

;-----------------------------------------------------------
; FindMin finds Min of global variables a, b and c
; and saves it in global variable min
;-----------------------------------------------------------
FindMin:		mov al, [a]
				cmp al, [b]
				ja bIsSmaller 	; b < a
				cmp al, [c]		; either a or c is min
				ja cIsSmallest	; a>c
				mov dl, al
				jmp return
bIsSmaller:		mov al, [c]
				cmp al, [b]
				ja bIsSmallest	; b < c		
				mov dl, [c]	; c is smallest	
				jmp return	
bIsSmallest:	mov dl, [b]
				jmp return
cIsSmallest:	mov dl, [c]	;dl = c		

return:			mov [min], dl	;*** Which instruction will be executed next?	
				;ret
;-----------------------------------------------------------
; FindMax finds Max of global variables a, b and c
; and saves it in global variable max
;-----------------------------------------------------------
FindMax:		mov al, [a]
				cmp al, [b]
				jb bIsGreater 	; b > a
				cmp al, [c]	; either a or c is max
				jb cIsGreatest	; c > a
				mov dl, al
				jmp returnFindMax
bIsGreater:		mov al, [c]
				cmp al, [b]
				jb bIsGreatest	; b < c		
				mov dl, [c]	; c is greatest	
				jmp returnFindMax	
bIsGreatest:	mov dl, [b]
				jmp returnFindMax
cIsGreatest:	mov dl, [c]	;dl = c		

returnFindMax:	mov [max], dl	;*** Which instruction will be executed next?	
				;ret		
;-----------------------------------------------------------
; FindTotal finds Total of global variables a, b and c
; and saves it in global variable total
;-----------------------------------------------------------
FindTotal:		sub sp, 2		; for total
			push bp
			mov bp, sp
			push ax
			push bx
			push cx
			
			mov al, 0
			add al, [a]
			add al, [b]
			add al, [c]
			mov [bp-2], al

			pop cx			; restoring state
			pop bx
			pop ax
			pop bp
			ret
			
;-----------------------------------------------------------
; FindAvg finds Average of global variables a, b and c
; by dividing total by 3
; and saves it in global variable avg
;-----------------------------------------------------------		
FindAvg:	mov al, [total]
			mov cl, 3
			div cl		;al = al/cl
			mov [avg], al
			jmp FindAns	;*** Which instruction will be executed next?	
			;ret
;-----------------------------------------------------------
; someFunc provides following functionality
; if ( avg > 0xC)
;		ans = max
;	else
;		ans = min
; where avg, min, max and ans are global variables
;-----------------------------------------------------------
someFunc:		jmp FindMin				
FindAns:		cmp byte[avg], 0xC
				jae AvgIsGreater
				mov al, [min]
				jmp ReturnFunc
AvgIsGreater:	mov al, [max]

ReturnFunc:		mov [ans], al	;*** Which instruction will be executed next?	
				ret				;*** Problem with commenting ret?
;-----------------------------------------------------------
start:		call someFunc

MOV  AX, 0x4C00         ; Terminate Program 
INT  0x21               

