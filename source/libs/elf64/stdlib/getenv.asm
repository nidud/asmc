; GETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

getenv proc uses rbx enval:string_t

    mov rbx,enval
    .ifd !strlen(enval)

	.return
    .endif

    mov edi,eax
    mov rsi,_environ
    lodsq

    .while rax

	.ifd !_strnicmp(rax, rbx, edi)

	    mov rax,[rsi-8]
	    add rax,rdi

	    .if ( byte ptr [rax] == '=' )
		.return( &[rax+1] )
	    .endif
	.endif
	lodsq
    .endw
    ret

getenv endp

    end
