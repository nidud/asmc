; _TSTRSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_tstrstart proc string:LPTSTR

    ldr rax,string

    .while 1

        movzx ecx,TCHAR ptr [rax]
        .if ( ecx == 9  ||
              ecx == 10 ||
              ecx == 13 ||
              ecx == ' ' )

            add rax,TCHAR
        .else
            .break
        .endif
    .endw
    ret

_tstrstart endp

    end
