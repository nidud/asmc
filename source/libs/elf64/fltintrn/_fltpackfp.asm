; _FLTPACKFP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltpackfp proc dst:ptr, src:ptr STRFLT

    xchg rsi,rdi
    _fltround(rdi)
    mov     rax,[rdi].STRFLT.mantissa.l
    mov     rdx,[rdi].STRFLT.mantissa.h
    mov     cx, [rdi].STRFLT.mantissa.e
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    mov     [rsi],rax
    mov     [rsi+8],rdx
    movaps  xmm0,[rsi]
    mov     rax,rsi
    ret

_fltpackfp endp

    end
