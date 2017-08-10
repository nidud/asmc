include intn.inc

.code

_qpow10 proc mantissa:ptr, exponent:dword

    xor edx,edx
    mov eax,mantissa
    mov [eax],edx
    mov [eax+4],edx
    mov [eax+8],edx
    mov [eax+12],edx
    .if exponent
        mov word ptr [eax+14],0x3FFF
        _normalizefq(eax, exponent)
    .endif
    ret

_qpow10 endp

    END
