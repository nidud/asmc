; _PCUMAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
ifndef __UNIX__
include winnls.inc
endif

public _pcumap
public _pclmap

.data
 _pcumap_table label byte
 i = 0
 while i lt 256
    if i lt 'a' or i gt 'z'
        db i
    else
        db i - 'a' + 'A'
    endif
    i = i + 1
 endm
 _pclmap_table label byte
 i = 0
 while i lt 256
    if i lt 'A' or i gt 'Z'
        db i
    else
        db i or 0x20
    endif
    i = i + 1
 endm
 _pclmap string_t _pclmap_table
 _pcumap string_t _pcumap_table

ifndef __UNIX__

.code

__initpcumap proc private uses rsi rdi

   .new lcid:LCID = GetUserDefaultLCID()

    .ifd LCMapStringA(lcid, LCMAP_UPPERCASE, _pcumap, 256, _pcumap, 256)

        .ifd LCMapStringA(lcid, LCMAP_LOWERCASE, _pclmap, 256, _pclmap, 256)

            .for ( rdx = _pctype, rsi = _pcumap, rdi = _pclmap, ecx = 0 : ecx < 256 : ecx++ )

                mov al,[rdx+rcx*2]
                and al,not (_LOWER or _UPPER)

                .if ( cl != [rsi+rcx] )

                    or al,_LOWER
                .elseif ( cl != [rdi+rcx] )

                    or al,_UPPER
                .endif
                mov [rdx+rcx*2],al
            .endf
        .endif
    .endif
    ret

__initpcumap endp

.pragma(init(__initpcumap, 51))
endif
    end
