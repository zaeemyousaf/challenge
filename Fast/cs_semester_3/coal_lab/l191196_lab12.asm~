[org 0x100]

jmp start

InitializeRecordKeeping:
			push bp
			mov bp, sp
			push di
			push cx
			
			mov cx, 0
			mov di, word[bp+4]
			mov cx, word[bp+6]
			
			sub cx, 2
			mov byte[di], cl
			inc di
			
			.Loop1:
			mov byte[di], '@'
			inc di
			dec cx
			jnz .Loop1
			
			mov cx, word[bp+6]
			mov byte[di], cl
			
			pop cx
			pop di
			pop bp
ret 4

AllocateBlock:
			push bp
			mov bp, sp
			push cx
			push di
			push si
			push ax
			
			mov cx, word[bp+4]
			mov di, EndOfProgram
			
			mov ax, cx
			add ax, 2
			
			cmp byte[di], cl
			jge .SkipError
			
			.Error:
			
			mov word[bp+6], 0xFFFF
			jmp .End
			
			.SkipError:
			
			
			

			mov ax, word[di]
			add di, ax
			inc di
			
			mov byte[di], 0
			sub di, cx
			sub di, 1
			mov byte[di], cl
			
			dec di
			sub byte[di], cl
			sub byte[di], 2
			mov si, di
			
			mov di, EndOfProgram
			sub byte[di], cl
			sub byte[di], 2
			
			inc si
			mov word[bp+6], si
			
			.End:
			
			pop ax
			pop si
			pop di
			pop cx
			pop bp
ret 2

start:

mov ax, 0
mov al, 10
push ax
push EndOfProgram
call InitializeRecordKeeping

push 0x0
push 0x0003
call AllocateBlock
pop ax

mov ax, 0x4c00
int 0x21

EndOfProgram: dw 0