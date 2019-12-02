; STREXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include crtl.inc

    .code

strext proc string:LPSTR

    mov string,strfn(string)

    .if strrchr(eax, '.')

        .if eax == string

            xor eax,eax
        .endif
    .endif
    ret

strext endp

    END
