; SETWARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; wchar_t **setwargv( int *argc, wchar_t *command_line );
;
; Note: The main array (__argv) is allocated in __wargv.asm
;
include stdlib.inc
include string.inc
include malloc.inc

MAXARGCOUNT equ 256
MAXARGSIZE  equ 0x8000	; Max argument size: 32K

	.code

setwargv proc uses rsi rdi rbx argc:ptr, cmdline:ptr wchar_t

local argv[MAXARGCOUNT]:QWORD
local buffer:QWORD

    mov buffer,alloca(MAXARGSIZE*2)
    mov rdi,buffer
    mov rsi,cmdline
    mov rdx,argc
    xor rax,rax
    mov [rdx],rax

    lodsw
    .while ax

	xor ecx,ecx		; Add a new argument
	xor edx,edx		; "quote from start" in EDX - remove
	mov [rdi],cx

	.for : ax == ' ' || (ax >= 9 && ax <= 13) :
	    lodsw
	.endf
	.break .if !ax		; end of command string
	.if ax == '"'
	    add edx,1
	    lodsw
	.endif
	.while ax == '"'	; ""A" B"
	    add ecx,1
	    lodsw
	.endw

	.while ax
	    .break .if !edx && !ecx && (ax == ' ' || (ax >= 9 && ax <= 13))
	    .if ax == '"'
		.if ecx
		    dec ecx
		.elseif edx
		    mov ax,[rsi]
		    .break .if ax == ' '
		    .break .if ax >= 9 && ax <= 13
		    dec edx
		.else
		    inc ecx
		.endif
	    .else
		stosw
	    .endif
	    lodsw
	.endw

	xor ecx,ecx
	mov [rdi],ecx
	lea rbx,[rdi+2]
	mov rdi,buffer
	.break .if cx == [rdi]
	push rax
	sub rbx,rdi
	memcpy(malloc(rbx), rdi, rbx)
	mov rdx,argc
	mov rcx,[rdx]
	mov argv[rcx*8],rax
	inc qword ptr [rdx]
	pop rax
	.break .if !( ecx < MAXARGCOUNT )
    .endw
    xor eax,eax
    mov rbx,argc
    mov rbx,[rbx]
    lea rdi,argv
    mov [rdi+rbx*8],rax
    lea rbx,[rbx*8+8]
    memcpy(malloc(rbx), rdi, rbx)
    ret

setwargv endp

    end
