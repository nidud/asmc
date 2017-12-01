; POWQ.ASM--
; Copyright (C) 2017 Asmc Developers
;
include quadmath.inc

.code

powq proc __cdecl base:PQFLOAT, exponent:PQFLOAT

    .repeat

        .if IsNaNq(rcx)

            mov rax,rcx
            .break
        .endif

        .if IsNaNq(rdx)

            mov rax,rdx
            .break
        .endif

        .if IsZeroq(rcx)

            .if IsZeroq(rdx)

                lea rax,_Q_NAN
            .else
                lea rax,_Q_ZERO
            .endif
            .break
        .endif

        .if IsZeroq(rdx)

            .if IsInfiniteq(rcx)

                lea rax,_Q_NAN
            .else
                lea rax,_Q_ONE
            .endif
            .break
        .endif

    .until 1
    ;movdqa xmm0,[rax]
    ret
powq endp

    end
