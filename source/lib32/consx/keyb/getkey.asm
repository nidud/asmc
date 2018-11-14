; GETKEY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

.code

getkey proc

    ReadEvent()
    PopEvent()
    ret

getkey endp

    END
