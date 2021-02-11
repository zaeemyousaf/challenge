; Author: Zaeem Yousaf (19L-1196 3E2) Homework 1
; A program that takes union of two ordered set of integers
;------------------------------- variable description
; ax will hold the element from set1
; bx will hold the element from set2
; cx will hold the previous inserted element
; ----------------------------------
; bp points to set1
; si points to set2
; di points to union
; ----------------------------------

[org 0x0100]		; preprocessor directive
jmp start
	

set1:	dw 1,4,6,0
set2:	dw 1,3,5,8,0
union:	dw 0,0,0,0,0,0,0,0,0,0 ;max ten

start:
	;; load addresses of set1 and set2 into registers
	mov bp, set1		; load set1 into base pointer
	mov si, set2		; load set2 into source index
	mov di,union		; load union into destination index
	
outerWhile:
	;; while element of set1 is not equal to zero
	mov ax, [bp]		;
	cmp ax, 0		; set1[index1] == 0
	je readRemainingSet2	; outer loop has finished
	;; while element of set2 is not equal to zero
	mov bx, [si]		;
	cmp bx, 0		; set2[index2] == 0
	je readRemainingSet1	;
	
	cmp ax, bx		; compare the values 
	ja insertItself		; jump to insertIt self if ax is greater than bx
	mov bx, [si]		; otherwise follow these lines
	mov [di], bx		;
	add di,2		;
	add si, 2		;

	add bp, 2
	jmp outerWhile


insertItself:
	mov bx, [si]		;
	mov [di], bx		;
	add di,2		;
	add si, 2		;
	;; --------------
	mov ax, [bp]		;
	mov [di], ax		;
	add di,2		;

	add bp, 2		;	
	jmp outerWhile		;

readRemainingSet1:
	mov ax, [bp]		;
	mov [di], ax		;
	add di,2		;
	add bp, 2		;
	cmp ax, 0	;
	jne readRemainingSet1	;
		
readRemainingSet2:
	mov bx, [si]		;
	mov [di], bx		;
	add di,2		;
	add si, 2		;
	cmp bx, 0	;
	jne readRemainingSet2	; if some elements are remaining then read it else exit
	
	mov AX, 0X4C00		; terminate the program
	int 0x21	
