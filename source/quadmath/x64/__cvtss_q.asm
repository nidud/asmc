; __CVTSS_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include errno.inc

    .code

__cvtss_q proc frame uses rdi rbx x:ptr, f:ptr

    mov edi,[rdx]
    mov ebx,edi     ; get exponent and sign
    shl edi,8       ; shift fraction into place
    sar ebx,32-9    ; shift to bottom
    xor bh,bh       ; isolate exponent
    .if bl
        .if bl != 0xFF
            add bx,0x3FFF-0x7F
        .else
            or bh,0x7F
            .if !( edi & 0x7FFFFFFF )
                ;
                ; Invalid exception
                ;
                or edi,0x40000000 ; QNaN
                _set_errno(EDOM)
            .endif
        .endif
        or edi,0x80000000
    .elseif edi
        or bx,0x3FFF-0x7F+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test edi,edi
            .break .ifs
            shl edi,1
            dec bx
        .endw
    .endif
    mov     rax,x
    shl     rdi,1+32
    add     ebx,ebx
    rcr     bx,1
    shrd    rdi,rbx,16
    mov     [rax+8],rdi
    xor     edx,edx
    mov     [rax],rdx
    ret

__cvtss_q endp

    end
