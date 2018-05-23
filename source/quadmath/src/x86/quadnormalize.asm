include quadmath.inc

.code

_lk_doscale proc private uses edi ebx

    mov ebx,eax
    lea edi,_Q_1E1
    .if esi >= 8192
        mov esi,8192    ; set to infinity multiplier
    .endif
    .if esi
        .repeat
            .if esi & 1
                quadmul(ebx, edi)
            .endif
            add edi,16
            shr esi,1
        .untilz
    .endif
    ret

_lk_doscale endp

_lk_scale proc private

  local factor:oword

    .if esi

        xor edx,edx
        lea eax,factor
        mov [eax],edx
        mov [eax+4],edx
        mov [eax+8],edx
        mov [eax+12],edx
        mov word ptr [eax+14],0x3FFF  ; 1.0
        .ifs esi < 0
            neg esi
            _lk_doscale()
            quaddiv(ebx, &factor)
        .else
            _lk_doscale()
            quadmul(ebx, &factor)
        .endif
    .endif
    ret

_lk_scale endp

quadnormalize proc uses esi edi ebx mantissa:ptr, exponent:SINT

    mov esi,exponent
    mov ebx,mantissa
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
    mov eax,ebx
    ret

quadnormalize endp

    END
