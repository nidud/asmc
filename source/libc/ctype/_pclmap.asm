; _PCLMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include stdio.inc
include malloc.inc
include winnls.inc

.data
_pclmap string_t NULL

.code

_init_pclmap proc private

    .if malloc(256)

        mov _pclmap,rax
        .for ( ecx = 0 : ecx < 256 : ecx++ )

            mov dl,cl
            .if ( cl >= 'A' && cl <= 'Z' )
                or dl,0x20
            .endif
            mov [rax+rcx],dl
        .endf

ifndef __UNIX__
       .new lcid:LCID = GetUserDefaultLCID()
        LCMapString(lcid, LCMAP_LOWERCASE, _pclmap, 255, _pclmap, 255)
endif
    .endif
    ret

_init_pclmap endp

_exit_pclmap proc private

    free(_pclmap)
    ret

_exit_pclmap endp

.pragma(init(_init_pclmap, 40))
.pragma(exit(_exit_pclmap, 40))

    end
