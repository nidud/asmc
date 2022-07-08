; CVTHQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

cvthq proc h:real2

ifdef _WIN64

    movd    eax,xmm0
    movsx   eax,ax              ; get half value
    mov     ecx,eax             ; get exponent and sign
    shl     eax,H_EXPBITS+16    ; shift fraction into place
    sar     ecx,15-H_EXPBITS    ; shift to bottom
    and     cx,H_EXPMASK        ; isolate exponent

    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if (eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                mov qerrno,EDOM
                mov ecx,0xFFFF
                mov eax,0x40000000 ; QNaN
            .else
                xor eax,eax
            .endif
        .endif
    .elseif eax
        or cx,Q_EXPBIAS-H_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test eax,eax
            .break .ifs
            shl eax,1
            dec cx
        .endw
    .endif

    shl ecx,1
    rcr cx,1
    shl rax,33
    shld rcx,rax,64-16
    movq xmm0,rcx
    shufpd xmm0,xmm0,1
else
    int 3
endif
    ret
cvthq endp

    end
