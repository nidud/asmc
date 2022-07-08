; CVTQSI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cvtqsi() - Quadruple float to __int128
;
include quadmath.inc

    .code

cvtqsi proc q:real16

ifdef _WIN64

    movq    r10,xmm0
    movhlps xmm0,xmm0
    movq    r11,xmm0
    shld    rcx,r11,16
    shld    r11,r10,16
    mov     r8d,ecx
    and     r8d,Q_EXPMASK

    .if ( r8d < Q_EXPBIAS )

        xor edx,edx
        xor eax,eax
        .if ( r8d == 0x3FFE )
            inc eax
        .endif

        .if ( ecx & 0x8000 )

            dec rax
            dec rdx
        .endif

    .elseif ( r8d > 128 + Q_EXPBIAS )

        xor eax,eax
        .if ( ecx & 0x8000 )
            mov rdx,_I64_MIN
        .else
            mov rdx,_I64_MAX
            dec rax
        .endif
        mov qerrno,ERANGE

    .else

        sub r8d,Q_EXPBIAS
        mov eax,1
        xor edx,edx

        .while r8d

            add r10,r10
            adc r11,r11
            adc rax,rax
            adc rdx,rdx
            dec r8d
        .endw

        add r11,r11
        adc rax,0
        adc rdx,0

        .if ( ecx & 0x8000 )

            neg rdx
            neg rax
            sbb rdx,0
        .endif
    .endif
else
    int 3
endif
    ret

cvtqsi endp

    end
