; _PCUMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include stdio.inc
include malloc.inc
include winnls.inc

.data
_pcumap string_t NULL

.code

_init_pcumap proc private

    .if malloc(256)

        mov _pcumap,rax
        .for ( ecx = 0: ecx < 256 : ecx++ )

            mov dl,cl
            .if ( cl >= 'a' && cl <= 'z' )
                and dl,0xDF
            .endif
            mov [rax+rcx],dl
        .endf
ifndef __UNIX__
       .new lcid:LCID = GetUserDefaultLCID()
        LCMapString(lcid, LCMAP_UPPERCASE, _pcumap, 255, _pcumap, 255)
endif
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
