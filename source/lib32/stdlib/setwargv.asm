; SETWARGV.ASM--
;
; wchar_t **setwargv( int *argc, wchar_t *command_line );
;
; Note: The main array (__wargv) is allocated in __wargv.asm
;
include stdlib.inc
include string.inc
include malloc.inc

MAXARGCOUNT equ 256
MAXARGSIZE  equ 0x8000	; Max argument size: 32K

	.code

	option	cstack:on

setwargv proc uses esi edi ebx argc:ptr, cmdline:ptr wchar_t

local argv[MAXARGCOUNT]:DWORD
local buffer:DWORD

    mov buffer,alloca(MAXARGSIZE*2)
    mov edi,buffer
    mov esi,cmdline
    mov edx,argc
    xor eax,eax
    mov [edx],eax

    lodsw
    .while ax

	xor ecx,ecx		; Add a new argument
	xor edx,edx		; "quote from start" in EDX - remove
	mov [edi],cx

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
		    mov ax,[esi]
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
	mov [edi],ecx
	lea ebx,[edi+2]
	mov edi,buffer
	.break .if cx == [edi]
	push eax
	sub ebx,edi
	memcpy(malloc(ebx), edi, ebx)
	mov edx,argc
	mov ecx,[edx]
	mov argv[ecx*4],eax
	inc dword ptr [edx]
	pop eax
	.break .if !( ecx < MAXARGCOUNT )
    .endw
    xor eax,eax
    mov ebx,argc
    mov ebx,[ebx]
    lea edi,argv
    mov [edi+ebx*4],eax
    lea ebx,[ebx*4+4]
    memcpy(malloc(ebx), edi, ebx)
    ret

setwargv endp

    end
