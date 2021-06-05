; _FLTUNPACK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltunpack proc p:ptr STRFLT, q:ptr

    mov     rax,[rdx]
    mov     r8,[rdx+8]
    shld    r9,r8,16
    shld    r8,rax,16
    shl     rax,16
    mov     [rcx].STRFLT.mantissa.e,r9w
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     r8,1
    rcr     rax,1
    mov     [rcx].STRFLT.mantissa.l,rax
    mov     [rcx].STRFLT.mantissa.h,r8
    mov     rax,rcx
    ret

_fltunpack endp

    end
