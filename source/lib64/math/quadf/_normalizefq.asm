include intn.inc

.code

_normalizefq proc uses rsi rdi rbx r12 mantissa:ptr, exponent:dword

  local factor:REAL16

    mov esi,edx ; exponent

    lea r12,factor

    xor edi,edi
    .ifs esi > 4096

        inc edi
    .else
        .ifs esi < -4096

            mov edi,2
        .endif
    .endif

    .if edi

        mov esi,4096

        xor eax,eax
        mov [r12],rax
        mov [r12+8],rax
        mov word ptr [r12+14],0x3FFF  ; 1.0
        lea rbx,_Q_1E1

        .repeat
            .if esi & 1

                _mulfq(r12, r12, rbx)
            .endif
            add rbx,16
            shr esi,1
        .untilz

        mov esi,exponent
        mov rbx,mantissa
        .if edi == 1
            _mulfq(rbx, rbx, r12)
            sub esi,4096
        .else
            _divfq(rbx, rbx, r12)
            add esi,4096
        .endif
    .endif

    .if esi

        xor ebx,ebx
        mov [r12],rbx
        mov [r12+8],rbx
        mov word ptr [r12+14],0x3FFF

        lea rdi,_Q_1E1

        .ifs esi < 0

            neg esi
            inc ebx
        .endif

        .if esi >= 8192

            mov esi,8192
        .endif

        .if esi
            .repeat
                .if esi & 1

                    _mulfq(r12, r12, rdi)
                .endif
                add rdi,16
                shr esi,1
            .untilz
        .endif

        mov  rax,mantissa
        xchg rax,rbx

        .if eax

            _divfq(rbx, rbx, r12)
        .else

            _mulfq(rbx, rbx, r12)
        .endif
    .endif
    mov rax,rbx
    ret

_normalizefq endp

    END
