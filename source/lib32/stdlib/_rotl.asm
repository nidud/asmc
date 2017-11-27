; _ROTL.ASM--
; Copyright (C) 2017 Asmc Developers
;
include stdlib.inc

.code

_rotl proc value:UINT, shift:SINT

    max_bits = sizeof(UINT) shl 3

    mov ecx,shift
    .ifs ( ecx < 0 )

        neg ecx
        _rotr(value, ecx)
    .else

        .if ( ecx > max_bits )
            and ecx,max_bits - 1
        .endif

        mov edx,value
        shl edx,cl
        mov eax,max_bits
        sub eax,ecx
        mov ecx,eax
        mov eax,value
        shr eax,cl
        or  eax,edx
    .endif
    ret

_rotl endp

    end
