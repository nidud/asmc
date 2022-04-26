; __CVTH_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include errno.inc

    .code

__cvth_q proc q:ptr, h:ptr

    push    rdi
    movsx   edx,word ptr [rsi]  ; get half value
    mov     ecx,edx             ; get exponent and sign
    shl     edx,H_EXPBITS+16    ; shift fraction into place
    sar     ecx,15-H_EXPBITS    ; shift to bottom
    and     cx,H_EXPMASK        ; isolate exponent

    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if (edx & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                _set_errno(EDOM)
                mov ecx,0xFFFF
                mov edx,0x40000000 ; QNaN
            .else
                xor edx,edx
            .endif
        .endif
    .elseif edx
        or cx,Q_EXPBIAS-H_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test edx,edx
            .break .ifs
            shl edx,1
            dec cx
        .endw
    .endif

    shl     ecx,1
    rcr     cx,1
    shl     rdx,33
    shld    rcx,rdx,64-16
    pop     rax
    mov     [rax+8],rcx
    xor     edx,edx
    mov     [rax],rdx
    ret

__cvth_q endp

    end
