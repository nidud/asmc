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

	option	cstack:on

setargv proc uses esi edi ebx argc:ptr, cmdline:ptr sbyte

local argv[MAXARGCOUNT]:DWORD
local buffer:DWORD

    mov buffer,alloca(MAXARGSIZE)
    mov edi,buffer
    mov esi,cmdline
    mov edx,argc
    xor eax,eax
    mov [edx],eax

    lodsb
    .while al

	xor ecx,ecx		; Add a new argument
	xor edx,edx		; "quote from start" in EDX - remove
	mov [edi],cl

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
		    mov al,[esi]
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
	mov [edi],cl
	lea ebx,[edi+1]
	mov edi,buffer
	.break .if cl == [edi]
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

setargv endp

    end
