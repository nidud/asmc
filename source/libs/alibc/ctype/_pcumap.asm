; _PCUMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

public _pcumap

.data
_pcumap string_t NULL

.code

_init_pcumap proc private

    .if malloc(256)

        mov _pcumap,rax
        .for ( ecx = 0: ecx < 256 : ecx++ )
            mov [rax+rcx],cl
        .endf
        .for ( rdx = _pcumap, al = 0xDF, ecx = 0: ecx < 256 : ecx++, rdx++ )
            .if ( cl >= 'a' && cl <= 'z' )
                and [rdx],al
            .endif
        .endf
    .endif
    ret

_init_pcumap endp


_exit_pcumap proc private

    free(_pcumap)
    ret

_exit_pcumap endp

.pragma(init(_init_pcumap, 40))
.pragma(exit(_exit_pcumap, 40))

    end
