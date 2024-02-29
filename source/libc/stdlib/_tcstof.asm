; STRTOF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include fltintrn.inc
include tchar.inc

    .code

_tcstof proc string:tstring_t, endptr:tarray_t

    ldr rcx,string
ifdef _UNICODE
    .new buffer[128]:char_t
    .new i:int_t = 0
    .for ( rdx = &buffer : i < lengthof(buffer) - 1 : i++, rdx++, rcx += 2 )

        mov ax,[rcx]
       .break .if ( !ax || ax > 0x7F )
        mov [rdx],al
    .endf
    mov byte ptr [rdx],0
    lea rcx,buffer
endif
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
ifdef _UNICODE
        lea rcx,buffer
        sub rdx,rcx
        add edx,edx
        add rdx,string
        mov rcx,endptr
endif
        mov [rcx],rdx
    .endif
    ret

_tcstof endp

    end
