; STRPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc
include crtl.inc

    .code

strpath PROC string:LPSTR

    .if strfn(string) != string

        mov byte ptr [eax-1],0
        mov eax,string
    .endif
    ret

strpath ENDP

    END
