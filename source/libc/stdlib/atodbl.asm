; _ATODBL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include math.inc
include fltintrn.inc

    .code

_atodbl proc dbl:ptr double_t, string:string_t

    mov rdx,_strtoflt( ldr(string) )
    mov rcx,dbl
    xor eax,eax
    mov [rcx],rax
ifndef _WIN64
    mov [ecx+4],eax
endif
    .if ( [rdx].STRFLT.flags & _ST_OVERFLOW )

        mov eax,_OVERFLOW
    .elseif ( [rdx].STRFLT.flags & _ST_UNDERFLOW )
        mov eax,_UNDERFLOW
    .else
        mov qerrno,0
        __cvtq_sd( rcx, rdx )
        xor eax,eax
        .if ( qerrno )
            mov eax,_OVERFLOW
        .endif
    .endif
    ret

_atodbl endp

    end
