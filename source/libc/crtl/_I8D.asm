; _I8D.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code

ifndef _WIN64

    option dotname

_I8D proc ; watcall dividend:int64_t, divisor:int64_t

    ;
    ; edx:eax / ecx:ebx --> edx:eax.ecx
    ;
    test    edx,edx     ; hi word of dividend
    js      .1          ; signed ?
    test    ecx,ecx     ; hi word of divisor
    js      .0          ; signed ?
    call    _U8D
    jmp     .3
.0:
    neg     ecx
    neg     ebx
    sbb     ecx,0
    call    _U8D
    neg     edx
    neg     eax
    sbb     edx,0
    jmp     .3
.1:
    neg     edx
    neg     eax
    sbb     edx,0
    test    ecx,ecx
    jns     .2
    neg     ecx
    neg     ebx
    sbb     ecx,0
    call    _U8D
    neg     ecx
    neg     ebx
    sbb     ecx,0
    jmp     .3
.2:
    call    _U8D
    neg     ecx
    neg     ebx
    sbb     ecx,0
    neg     edx
    neg     eax
    sbb     edx,0
.3:
    ret

_I8D endp

else
    int     3
endif
    end

