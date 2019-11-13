; ISINFQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

isinfq proc vectorcall V:real16

    xor  eax,eax
    movq r10,xmm0

    .if !r10

        shufpd  xmm0,xmm0,1
        movq    r10,xmm0
        shufpd  xmm0,xmm0,1

        .if !r10d

            shr r10,32
            and r10d,0x7FFFFFFF
            cmp r10d,0x7FFF0000
            setz al
        .endif
    .endif
    ret

isinfq endp

    end
