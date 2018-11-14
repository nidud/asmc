; FTOQUAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert float to quad float
;
include quadmath.inc

    .code

ftoquad proc p:ptr, f:ptr

    mov ecx,f               ; get float value
    mov eax,[ecx]
    mov ecx,eax             ; get exponent and sign
    shl eax,F_EXPBITS       ; shift fraction into place
    sar ecx,F_SIGBITS-1     ; shift to bottom
    xor ch,ch               ; isolate exponent
    .if cl
        .if cl != 0xFF
            add cx,Q_EXPBIAS-F_EXPBIAS
        .else
            or ch,0x7F
            .if !(eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                or eax,0x40000000 ; QNaN
                mov qerrno,EDOM
            .endif
        .endif
        or eax,0x80000000
    .elseif eax
        or cx,Q_EXPBIAS-F_EXPBIAS+1 ; set exponent
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

ftoquad endp

    end
