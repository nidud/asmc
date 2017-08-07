include intn.inc

.data

qpow10_table label oword
    oword 0x40024000000000000000000000000000 ; 1e1
    oword 0x40059000000000000000000000000000 ; 1e2
    oword 0x400C3880000000000000000000000000 ; 1e4
    oword 0x40197D78400000000000000000000000 ; 1e8
    oword 0x40341C37937E08000000000000000000 ; 1e16
    oword 0x40693B8B5B5056E16B3BE04000000000 ; 1e32
    oword 0x40D384F03E93FF9F4DAA797ED6E38ED6 ; 1e64
    oword 0x41A827748F9301D319BF8CDE66D86D62 ; 1e128
    oword 0x435154FDD7F73BF3BD1BBB77203731FE ; 1e256
    oword 0x46A3C633415D4C1D238D98CAB8A978A1 ; 1e512
    oword 0x4D4892ECEB0D02EA182ECA1A7A51E317 ; 1e1024
    oword 0x5A923D1676BB8A7ABBC94E9A519C6536 ; 1e2048
    oword 0x752588C0A40514412F3592982A7F0095 ; 1e4096 - 88C0A40514412F3592982A7F00949524
    oword 0x7FFF0000000000000000000000000000 ; 1e8192 - Infinity

.code

_lk_doscale proc private uses edi ebx
    mov ebx,eax
    xor edi,edi
    .if esi >= 8192
        mov esi,8192    ; set to infinity multiplier
    .endif
    .if esi
        .repeat
            .if esi & 1
                mov eax,ebx
                mov ecx,ebx
                lea edx,qpow10_table[edi]
                _lk_mulfq()
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
            mov eax,ebx
            mov ecx,ebx
            lea edx,factor
            _lk_divfq()
        .else
            _lk_doscale()
            mov eax,ebx
            mov ecx,ebx
            lea edx,factor
            _lk_mulfq()
        .endif
    .endif
    ret
_lk_scale endp

_normalizefq proc uses esi edi ebx mantissa:ptr, exponent:dword
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
    ret
_normalizefq endp

    END
