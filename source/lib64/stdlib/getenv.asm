; GETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

getenv proc uses rsi rdi rbx rcx enval:LPSTR

    mov rbx,rcx
    .if strlen(rcx)

	mov rdi,rax
	mov rsi,_environ
	lodsq

	.while rax
	    .if !_strnicmp(rax, rbx, rdi)

		mov rax,[rsi-8]
		add rax,rdi

		.if byte ptr [rax] == '='

		    inc rax
		    .break
		.endif

	    .endif
	    lodsq
	.endw
    .endif
    ret

getenv endp

    END
