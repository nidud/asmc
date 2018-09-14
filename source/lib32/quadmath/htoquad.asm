;
; Convert half to quad float
;
include quadmath.inc

    .code

htoquad proc p:ptr, h:ptr

    mov ecx,h               ; get half value
    movsx eax,word ptr [ecx]
    mov ecx,eax             ; get exponent and sign
    shl eax,H_EXPBITS+16    ; shift fraction into place
    sar ecx,15-H_EXPBITS    ; shift to bottom
    and cx,H_EXPMASK        ; isolate exponent
    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if (eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                mov ecx,Q_EXPMASK
                mov eax,0x40000000 ; QNaN
                mov qerrno,EDOM
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
    mov edx,p
    shl eax,1
    xchg eax,edx
    mov [eax+10],edx
    xor edx,edx
    mov [eax],edx
    mov [eax+4],edx
    mov [eax+8],dx
    shl ecx,1
    rcr cx,1
    mov [eax+14],cx
    ret

htoquad endp

    end
