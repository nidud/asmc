; STRTOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fltintrn.inc

    .code

strtof proc string:string_t, endptr:array_t

    ldr rcx,string
    _strtoflt( rcx )
    __cvtq_ss( rax, rax )
ifdef __SSE__
    movss xmm0,[rax]
else
    fld real4 ptr [rax]
endif
    mov rcx,endptr
    .if ( rcx )

        mov rdx,[rax].STRFLT.string
        mov [rcx],rdx
    .endif
    ret

strtof endp

    end
