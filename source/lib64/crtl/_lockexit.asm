; _LOCKEXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include internal.inc

    .code

_lockexit proc

    _mlock(_EXIT_LOCK1)
    ret

_lockexit endp

_unlockexit proc

    _munlock(_EXIT_LOCK1)
    ret

_unlockexit endp

    end
