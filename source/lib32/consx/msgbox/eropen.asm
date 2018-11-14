; EROPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

errnomsg proto :LPSTR, :LPSTR, :LPSTR

    .code

eropen proc file:LPSTR

    errnomsg("Error open file", "Can't open the file:\n%s\n\n%s", file)
    ret

eropen endp

    END
