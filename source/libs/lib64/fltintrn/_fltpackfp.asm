; _FLTPACKFP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltpackfp proc q:ptr, p:ptr STRFLT

    _fltround(rdx)

    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
    mov     cx, [rcx].STRFLT.mantissa.e
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    mov     rcx,p
    mov     [rcx],rax
    mov     [rcx+8],rdx
    movaps  xmm0,[rcx]
    mov     rax,rcx
    ret

_fltpackfp endp

    end
