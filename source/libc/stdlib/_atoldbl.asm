; _ATOLDBL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include math.inc
include fltintrn.inc

    .code

_atoldbl proc ldbl:ptr ldouble_t, string:string_t

    ldr rcx,string
    mov rdx,_strtoflt( rcx )
    mov rcx,ldbl
    xor eax,eax
    mov [rcx],rax
    mov [rcx+8],ax
ifndef _WIN64
    mov [ecx+4],eax
endif
    .if ( [rdx].STRFLT.flags & _ST_OVERFLOW )

        mov eax,_OVERFLOW
    .elseif ( [rdx].STRFLT.flags & _ST_UNDERFLOW )
        mov eax,_UNDERFLOW
    .else
        mov qerrno,0
        __cvtq_ld( rcx, rdx )
        xor eax,eax
        .if ( qerrno )
            mov eax,_OVERFLOW
        .endif
    .endif
    ret

_atoldbl endp

    end
