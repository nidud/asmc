; _FLTUNPACK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltunpack proc p:ptr STRFLT, q:ptr

    mov     rax,[rsi]
    mov     rdx,[rsi+8]
    shld    rcx,rdx,16
    shld    rdx,rax,16
    shl     rax,16
    mov     [rdi].STRFLT.mantissa.e,cx
    and     ecx,Q_EXPMASK
    neg     ecx
    rcr     rdx,1
    rcr     rax,1
    mov     [rdi].STRFLT.mantissa.l,rax
    mov     [rdi].STRFLT.mantissa.h,rdx
    mov     rax,rdi
    ret

_fltunpack endp

    end
