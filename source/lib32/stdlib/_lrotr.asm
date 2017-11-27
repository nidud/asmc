; _LROTR.ASM--
; Copyright (C) 2017 Asmc Developers
;
include stdlib.inc

.code

_lrotr proc value:ULONG, shift:SINT

    max_bits = sizeof(ULONG) shl 3

    mov ecx,shift
    .ifs ( ecx < 0 )

        neg ecx
        _lrotl(value, ecx)
    .else

        .if ( ecx > max_bits )
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

_lrotr endp

    end
