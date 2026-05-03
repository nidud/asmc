; CTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include ctype.inc
include locale.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

%   _tprintf(" &_istupper&:\t")
    .for ( ebx = 'A' : ebx < 256 : ebx++ )

        .if ( _istupper(ebx) )
            _tprintf("%c", ebx)
        .endif
    .endf
%   _tprintf("\n &_istlower&:\t")
    .for ( ebx = 'A' : ebx < 256 : ebx++ )

        .if ( _istlower(ebx) )
            _tprintf("%c", ebx)
        .endif
    .endf
    _tprintf("\n")

    _tprintf("_tsetlocale(\"\"): %s\n", _tsetlocale(LC_CTYPE, "") )

%   _tprintf(" &_istupper&:\t")
    .for ( ebx = 'A' : ebx < 256 : ebx++ )

        .if ( _istupper(ebx) )
            _tprintf("%c", ebx)
        .endif
    .endf
%   _tprintf("\n &_istlower&:\t")
    .for ( ebx = 'A' : ebx < 256 : ebx++ )

        .if ( _istlower(ebx) )
            _tprintf("%c", ebx)
        .endif
    .endf
    _tprintf("\n")
    xor eax,eax
    ret

_tmain endp

    end _tstart
