; _TTOQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include math.inc
include fltintrn.inc

    .code

_ttoqf proc p:ptr real16, string:tstring_t

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

_ttoqf endp

    end
