; STREXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include crtl.inc

    .code

strext proc uses rsi string:LPSTR

    mov rsi,strfn(rcx)

    .if strrchr(rsi, '.')

        .if rax == rsi

            xor eax,eax
        .endif
    .endif
    ret

strext endp

    END
