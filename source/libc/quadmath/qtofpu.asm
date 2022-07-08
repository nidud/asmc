; QTOFPU.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

    option dotname

qtofpu proc q:real16
ifdef _WIN64
   .new     ld:real10
    xor     ecx,ecx
    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    shld    rcx,rdx,16
    shld    rdx,rax,16
    mov     eax,ecx
    and     eax,LD_EXPMASK
    neg     eax
    mov     rax,rdx
    rcr     rax,1
    jnc     .1 ; round result
    cmp     rax,-1
    jne     .0
    mov     rax,0x8000000000000000
    inc     cx
    jmp     .1
.0:
    add     rax,1
.1:
    mov     qword ptr ld,rax
    mov     word ptr ld[8],cx
    fld     ld
else
    int     3
endif
    ret
qtofpu endp

    end
