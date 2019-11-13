; GETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

getenv proc uses rsi rdi enval:string_t

    .return .ifd !strlen(rcx)

    mov edi,eax
    mov rsi,_environ
    lodsq

    .while rax

	.ifd !_strnicmp(rax, enval, edi)

	    mov rax,[rsi-8]
	    add rax,rdi

	    .return( &[rax+1] ) .if byte ptr [rax] == '='
	.endif
	lodsq
    .endw
    ret

getenv endp

    END
