; _ATOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include math.inc
include fltintrn.inc

    .code

_atoflt proc flt:ptr float_t, string:string_t

    mov rdx,_strtoflt( ldr(string) )
    mov rcx,flt
    xor eax,eax
    mov [rcx],eax
    .if ( [rdx].STRFLT.flags & _ST_OVERFLOW )
        mov eax,_OVERFLOW
    .elseif ( [rdx].STRFLT.flags & _ST_UNDERFLOW )
        mov eax,_UNDERFLOW
    .else
        mov qerrno,0
        __cvtq_ss( rcx, rdx )
        xor eax,eax
        .if ( qerrno )
            mov eax,_OVERFLOW
        .endif
    .endif
    ret

_atoflt endp

    end
