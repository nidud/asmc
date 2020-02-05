; SETFEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include crtl.inc
include strlib.inc

    .code

setfext PROC path:LPSTR, ext:LPSTR

    .if strext(path)

        mov byte ptr [eax],0
    .endif
    strcat(path, ext)
    ret

setfext ENDP

    END
