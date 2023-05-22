; __CVTH_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc
include errno.inc

    .code

__cvth_q proc __ccall q:ptr qfloat_t, h:ptr half_t

    ldr     rax,q
    ldr     rdx,h

    movsx   edx,word ptr [rdx]
    mov     ecx,edx             ; get exponent and sign
    shl     edx,H_EXPBITS+16    ; shift fraction into place
    sar     ecx,15-H_EXPBITS    ; shift to bottom
    and     cx,H_EXPMASK        ; isolate exponent

    .if ( cl )
        .if ( cl != H_EXPMASK )
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if ( edx & 0x7FFFFFFF )
                ;
                ; Invalid exception
                ;
                mov qerrno,EDOM
                mov ecx,0xFFFF
                mov edx,0x40000000 ; QNaN
            .else
                xor edx,edx
            .endif
        .endif

    .elseif ( edx )

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

    shl ecx,1
    rcr cx,1
    mov [rax+14],cx
    shl edx,1
    mov [rax+10],edx
    xor edx,edx
    mov [rax],rdx
ifndef _WIN64
    mov [rax+4],edx
endif
    mov [rax+8],edx
    ret

__cvth_q endp

    end
