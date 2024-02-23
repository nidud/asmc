; _ATOQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include math.inc
include fltintrn.inc

    .code

_atoqf proc p:ptr real16, string:string_t

    ldr rcx,string
    mov rdx,_strtoflt( rcx )
    mov rcx,p
    xor eax,eax
    mov [rcx],rax
    mov [rcx+8],rax
ifndef _WIN64
    mov [ecx+4],eax
    mov [ecx+12],eax
endif
    .if ( [rdx].STRFLT.flags & _ST_OVERFLOW )

        mov eax,_OVERFLOW
    .elseif ( [rdx].STRFLT.flags & _ST_UNDERFLOW )
        mov eax,_UNDERFLOW
    .else
        mov [rcx],oword ptr [rdx]
        xor eax,eax
    .endif
    ret

_atoqf endp

    end
