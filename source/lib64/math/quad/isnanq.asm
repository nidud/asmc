; ISNANQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

isnanq proc vectorcall V:XQFLOAT

    shufpd  xmm0,xmm0,1
    movq    r10,xmm0
    shufpd  xmm0,xmm0,1
    rol     r10,16
    and     r10w,Q_EXPMASK
    xor     eax,eax

    .if r10w == Q_EXPMASK

        shr r10,16
        .ifz
            movq r10,xmm0
        .endif
        test r10,r10
        setnz al
    .endif
    ret

isnanq endp

    end
