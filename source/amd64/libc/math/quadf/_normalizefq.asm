include intn.inc

.code

_lk_doscale proc private uses rdi rbx

    mov rbx,rax
    lea rdi,_Q_1E1
    .if esi >= 8192
        mov esi,8192    ; set to infinity multiplier
    .endif
    .if esi
        .repeat
            .if esi & 1
                _mulfq(rbx, rbx, rdi)
            .endif
            add rdi,16
            shr esi,1
        .untilz
    .endif
    ret

_lk_doscale endp

_lk_scale proc private

  local factor:oword

    .if esi

        xor edx,edx
        lea rax,factor
        mov [rax],rdx
        mov [rax+8],rdx
        mov word ptr [rax+14],0x3FFF  ; 1.0

        .ifs esi < 0
            neg esi
            _lk_doscale()
            _divfq(rbx, rbx, &factor)
        .else
            _lk_doscale()
            _mulfq(rbx, rbx, &factor)
        .endif
    .endif
    ret

_lk_scale endp

_normalizefq proc uses rsi rdi rbx mantissa:ptr, exponent:dword

    mov esi,exponent
    mov rbx,mantissa
    .ifs esi > 4096
        mov esi,4096
        _lk_scale()
        mov esi,exponent
        sub esi,4096
    .else
        .ifs esi < -4096
            mov esi,-4096
            _lk_scale()
            mov esi,exponent
            add esi,4096
        .endif
    .endif
    _lk_scale()
    mov rax,rbx
    ret

_normalizefq endp

    END
