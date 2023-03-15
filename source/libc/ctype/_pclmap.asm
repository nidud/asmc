; _PCLMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include winnls.inc

public _pclmap

.data
_pclmap string_t NULL

.code

_init_pclmap proc private

   .new lcid:LCID = GetUserDefaultLCID()
    .if malloc(256)

        mov _pclmap,rax
        .for ( edx = 0: edx < 256 : edx++ )
            mov [rax+rdx],dl
        .endf
        .if !LCMapString(lcid, LCMAP_LOWERCASE, _pclmap, 255, _pclmap, 255)

            .for ( rdx = _pclmap, al = 0x20, ecx = 0: ecx < 256 : ecx++, rdx++ )
                .if ( cl >= 'A' && cl <= 'Z' )

                    or [rdx],al
                .endif
            .endf
        .endif
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
