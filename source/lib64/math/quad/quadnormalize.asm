; QUADNORMALIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

.code

quadnormalize proc uses rbx r12 r13 r14 q:ptr, exponent:SINT

  local factor:U128

    mov r12d,edx
    mov r14,rcx
    xor r13d,r13d
    .ifs r12d > 4096
        inc r13d
    .else
        .ifs r12d < -4096
            mov r13d,2
        .endif
    .endif

    .if r13d

        mov r12d,4096

        xor eax,eax
        mov factor.m64[0],rax
        mov factor.m64[8],rax
        mov factor.m16[14],Q_EXPBIAS ; 1.0
        lea rbx,_Q_1E1
        .repeat
            .if r12d & 1
                quadmul(&factor, rbx)
            .endif
            add rbx,16
            shr r12d,1
        .untilz
        mov r12d,exponent
        .if r13d == 1
            quadmul(r14, &factor)
            sub r12d,4096
        .else
            quaddiv(r14, &factor)
            add r12d,4096
        .endif
    .endif

    .if r12d

        xor ebx,ebx
        mov factor.m64[0],rbx
        mov factor.m64[8],rbx
        mov factor.m16[14],Q_EXPBIAS ; 1.0

        lea r13,_Q_1E1
        .ifs r12d < 0
            neg r12d
            inc ebx
        .endif
        .if r12d >= 8192
            mov r12d,8192
        .endif
        .if r12d
            .repeat
                .if r12d & 1
                    quadmul(&factor, r13)
                .endif
                add r13,16
                shr r12d,1
            .untilz
        .endif
        .if ebx
            quaddiv(r14, &factor)
        .else
            quadmul(r14, &factor)
        .endif
    .endif
    mov rax,r14
    ret

quadnormalize endp

    END
