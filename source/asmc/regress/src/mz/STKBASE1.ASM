
;--- v2.17: using "option stackbase" and "assume ss" to
;--- define PROCs with different offset magnitudes for CS and SS.
;--- both PROC and INVOKE are aware of that.

	.286
	.model tiny
	.stack 1024
	.386

;--- an empty 32-bit stack segment for assume
STACK32 segment use32 stack 'STACK'
STACK32 ends

	.data

text1 db "hello",10,0

	.code

	assume ss:stack32
	option stackbase:ebp	; switch stackbase to 32-bit register

;--- printf: proc assumes 32-bit stack

printf PROC c uses si edi fmt:ptr, args:vararg

local longarg:byte

	lea edi, args
	mov si, fmt
@@:
	lodsb
	mov bh, 0
	mov ah, 0Eh
	int 10h
	and al, al
	jnz @B
	ret

printf ENDP

;--- calling printf() from another proc with 32-bit stack

test1 proc

local v1:word

	invoke printf, addr text1, [v1]
	ret

test1 endp

;--- switch stack back to 16-bit

	assume ss:dgroup
	option stackbase:bp

main proc

local v1:word

;--- calling printf() as near is possible, of course,
;--- must just be ensured that hiword ESP is clear
	movzx esp, sp
	invoke printf, addr text1, [v1]
	ret

main endp

start:
	mov ax, dgroup
	mov ds, ax
	mov bx, ss
	sub bx, ax
	shl bx, 4
	mov ss, ax
	add sp, bx
	call main
	mov ax,4c00h
	int 21h

	END start

