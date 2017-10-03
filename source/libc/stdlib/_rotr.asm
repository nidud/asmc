; _ROTR.ASM--
; Copyright (C) 2017 Asmc Developers
;
include stdlib.inc

.code

_rotr proc value:UINT, shift:SINT

    max_bits = sizeof(UINT) shl 3

    mov ecx,shift
    .ifs ( ecx < 0 )

        neg ecx
        _rotl(value, ecx)
    .else

        .if ( ecx > max_bits shl 3 )
            and ecx,max_bits - 1
        .endif

        mov edx,value
        shr edx,cl
        mov eax,max_bits
        sub eax,ecx
        mov ecx,eax
        mov eax,value
        shl eax,cl
        or  eax,edx
    .endif
    ret

_rotr endp

    end
