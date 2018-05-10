; POWQ.ASM--
; Copyright (C) 2017 Asmc Developers
;
include quadmath.inc

.code

powq proc __cdecl base:PQFLOAT, exponent:PQFLOAT

  local temp:REAL16

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

        .if IsInfiniteq(rcx)

            .if IsInfiniteq(rdx)

                .if byte ptr [rdx+15] & 0x80
                    lea rax,_Q_ZERO
                    .break
                .endif
                mov rax,rcx
                .break
            .endif
            ;.if byte ptr [rdx+15] & 0x80
                lea rax,_Q_INF
            ;.endif
            .break
        .endif

        .if IsInfiniteq(rdx)

            .if byte ptr [rdx+15] & 0x80
                lea rax,_Q_ZERO
                .break
            .endif
            ;.if byte ptr [rdx+15] & 0x80
                lea rax,_Q_INF
            ;.endif
            .break
        .endif

        mov rax,qword ptr _Q_ONE
        .if rax == [rcx]
            mov rax,qword ptr _Q_ONE[8]
            .if rax == [rcx+8]
                lea rax,_Q_ONE
                .break
            .endif
        .endif

        log2q(rcx)
        movdqa temp,xmm0
        _mulfq(&temp, exponent, &temp)

    .until 1
    movdqa xmm0,[rax]
    ret
powq endp

    end
