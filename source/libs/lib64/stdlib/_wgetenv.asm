; _WGETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

_wgetenv proc uses rsi rdi enval:wstring_t

    .return .ifd !wcslen(rcx)

    mov edi,eax
    mov rsi,_wenviron
    lodsq

    .while rax

	.ifd !_wcsnicmp(rax, enval, edi)

	    mov rax,[rsi-8]
	    lea rax,[rdi*2+rax]

	    .return( &[rax+2] ) .if word ptr [rax] == '='
	.endif
	lodsq
    .endw
    ret

_wgetenv endp

    END
