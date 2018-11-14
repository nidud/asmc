; NORMALIZEQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

normalizeq proc vectorcall uses rsi rdi rbx r12 x:XQFLOAT, exponent:SINT

    mov edi,edx
    xor ebx,ebx
    .ifs edx > 4096
        inc ebx
    .else
        .ifs edx < -4096
            mov ebx,2
        .endif
    .endif

    .if ebx

        movaps  xmm2,xmm0
        mov     eax,0x3FFF0000
        movd    xmm0,eax
        shufps  xmm0,xmm0,00010101B

        mov r12d,4096
        lea rsi,_Q_1E1
        .repeat
            .if r12d & 1
                mulq(xmm0, [rsi])
            .endif
            add rsi,16
            shr r12d,1
        .untilz

        movaps xmm1,xmm0
        .if ebx == 1
            mulq(xmm2, xmm1)
            sub edi,4096
        .else
            divq(xmm2, xmm1)
            add edi,4096
        .endif
    .endif

    .if edi

        movaps  xmm2,xmm0
        mov     eax,0x3FFF0000
        movd    xmm0,eax
        shufps  xmm0,xmm0,00010101B

        xor ebx,ebx
        .ifs edi < 0
            neg edi
            inc ebx
        .endif
        .if edi >= 8192
            mov edi,8192
        .endif

        .if edi
            lea rsi,_Q_1E1
            .repeat
                .if edi & 1
                    mulq(xmm0, [rsi])
                .endif
                add rsi,16
                shr edi,1
            .untilz
        .endif
        movaps xmm1,xmm0
        .if ebx
            divq(xmm2, xmm1)
        .else
            mulq(xmm2, xmm1)
        .endif
    .endif
    ret

normalizeq endp

    END
