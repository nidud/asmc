; FGETCHAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

_fgetchar proc
    .return(getc(stdin))
_fgetchar endp

getchar proc
    .return _fgetchar()
getchar endp

    end
