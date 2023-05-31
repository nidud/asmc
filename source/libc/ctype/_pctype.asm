; _PCTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

.data
_pctype LPWORD _ctype+2 ; pointer to table for char's

.code

__initpctype proc private uses rsi rdi

    .for ( rdx = _pctype,
           rsi = _pcumap,
           rdi = _pclmap,
           ecx = 0 : ecx < 256 : ecx++ )

        mov al,[rdx+rcx*2]
        and al,not (_LOWER or _UPPER)

        .if ( cl != [rsi+rcx] )

            or al,_LOWER
        .elseif ( cl != [rdi+rcx] )

            or al,_UPPER
        .endif
        mov [rdx+rcx*2],al
    .endf
    ret

__initpctype endp

.pragma(init(__initpctype, 50))

    end
