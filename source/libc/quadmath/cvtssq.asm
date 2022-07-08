; CVTSSQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

    option dotname

cvtssq proc f:real4
ifdef _WIN64
    movd    edx,xmm0
    mov     ecx,edx     ; get exponent and sign
    shl     edx,8       ; shift fraction into place
    sar     ecx,32-9    ; shift to bottom
    xor     ch,ch       ; isolate exponent
    test    cl,cl
    jz      .1
    cmp     cl,0xFF
    je      .0
    add     cx,0x3FFF-0x7F
    jmp     .3
.0:
    or      ch,0xFF
    test    edx,0x7FFFFFFF
    jnz     .3          ; Invalid exception
    or      edx,0x40000000
    mov     qerrno,EDOM
    jmp     .3
.1:
    test    edx,edx
    jz      .3
    or      cx,0x3FFF-0x7F+1
.2:
    test    edx,edx     ; normalize number
    js      .3
    shl     edx,1
    dec     cx
    jmp     .2
.3:
    shl     rdx,1+32
    add     ecx,ecx
    rcr     cx,1
    shrd    rdx,rcx,16
    movq    xmm0,rdx
    shufpd  xmm0,xmm0,1
else
    int     3
endif
    ret
cvtssq endp

    end
