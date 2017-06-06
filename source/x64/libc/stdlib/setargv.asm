; SETARGV.ASM--
;
; char **setargv( int *argc, char *command_line );
;
; Note: The main array (__argv) is allocated in __argv.asm
;
include stdlib.inc
include string.inc
include alloc.inc

MAXARGCOUNT equ 256
MAXARGSIZE  equ 0x8000	; Max argument size: 32K

	.code

setargv proc uses rsi rdi rbx argc:ptr, cmdline:ptr sbyte

local argv[MAXARGCOUNT]:QWORD
local buffer:QWORD

    mov buffer,alloca(MAXARGSIZE)
    mov rdi,buffer
    mov rsi,cmdline
    mov rdx,argc
    xor rax,rax
    mov [rdx],rax

    lodsb
    .while al

	xor ecx,ecx		; Add a new argument
	xor edx,edx		; "quote from start" in EDX - remove
	mov [rdi],cl

	.for : al == ' ' || (al >= 9 && al <= 13) :
	    lodsb
	.endf
	.break .if !al		; end of command string
	.if al == '"'
	    add edx,1
	    lodsb
	.endif
	.while al == '"'	; ""A" B"
	    add ecx,1
	    lodsb
	.endw

	.while al
	    .break .if !edx && !ecx && (al == ' ' || (al >= 9 && al <= 13))
	    .if al == '"'
		.if ecx
		    dec ecx
		.elseif edx
		    mov al,[rsi]
		    .break .if al == ' '
		    .break .if al >= 9 && al <= 13
		    dec edx
		.else
		    inc ecx
		.endif
	    .else
		stosb
	    .endif
	    lodsb
	.endw

	xor ecx,ecx
	mov [rdi],ecx
	lea rbx,[rdi+1]
	mov rdi,buffer
	.break .if cl == [rdi]
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

setargv endp

    end
