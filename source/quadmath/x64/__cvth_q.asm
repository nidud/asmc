; __CVTH_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include errno.inc

    .code

__cvth_q proc frame x:ptr, h:ptr

    movsx eax,word ptr [rdx]    ; get half value
    mov ecx,eax                 ; get exponent and sign
    shl eax,H_EXPBITS+16        ; shift fraction into place
    sar ecx,15-H_EXPBITS        ; shift to bottom
    and cx,H_EXPMASK            ; isolate exponent

    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if (eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                _set_errno(EDOM)
                mov ecx,Q_EXPMASK
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

    mov rdx,x
    shl eax,1
    mov [rdx+10],eax
    xor eax,eax
    mov [rdx],rax
    mov [rdx+8],ax
    shl ecx,1
    rcr cx,1
    mov [rdx+14],cx
    mov rax,rdx
    ret

__cvth_q endp

    end
