; _WGETCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc

    .code

_wgetcwd proc buffer:LPWSTR, maxlen:SINT

    _wgetdcwd( 0, buffer, maxlen )
    ret

_wgetcwd endp

    end
