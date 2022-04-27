; CVTSS_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include errno.inc

    .code

    option win64:noauto

cvtss_q proc f:real4

    movd edx,xmm0
    mov ecx,edx     ; get exponent and sign
    shl edx,8       ; shift fraction into place
    sar ecx,32-9    ; shift to bottom
    xor ch,ch       ; isolate exponent
    .if cl
        .if cl != 0xFF
            add cx,0x3FFF-0x7F
        .else
            or ch,0xFF
            .if !( edx & 0x7FFFFFFF )

                ; Invalid exception

                or edx,0x40000000 ; QNaN
                mov errno,EDOM
            .endif
        .endif
        ;or edx,0x80000000
    .elseif edx
        or cx,0x3FFF-0x7F+1 ; set exponent
        .while 1

            ; normalize number

            test edx,edx
            .break .ifs
            shl edx,1
            dec cx
        .endw
    .endif
    shl     rdx,1+32
    add     ecx,ecx
    rcr     cx,1
    shrd    rdx,rcx,16
    movq    xmm0,rdx
    shufpd  xmm0,xmm0,1
    ret

cvtss_q endp

    end
