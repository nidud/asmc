; _LROTL.ASM--
; Copyright (C) 2017 Asmc Developers
;
include stdlib.inc

.code

_lrotl proc value:ULONG, shift:SINT

    max_bits = sizeof(ULONG) shl 3

    mov ecx,shift
    .ifs ( ecx < 0 )

        neg ecx
        _lrotr(value, ecx)
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

_lrotl endp

    end
