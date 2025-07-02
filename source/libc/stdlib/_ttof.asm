; _TTOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fltintrn.inc
include tchar.inc

    .code

_ttof proc string:tstring_t

    ldr rcx,string
ifdef _UNICODE
    .new buf[128]:char_t
    .new i:int_t = 0
    .for ( rdx = &buf : i < lengthof(buf) - 1 : i++, rdx++, rcx += 2 )

        mov ax,[rcx]
       .break .if ( !ax || ax > 0x7F )
        mov [rdx],al
    .endf
    mov byte ptr [rdx],0
    lea rcx,buf
endif
    _strtoflt( rcx )
    __cvtq_sd( rax, rax )
ifdef __SSE__
    movsd xmm0,[rax]
else
    fld real8 ptr [rax]
endif
    ret

_ttof endp

    end
