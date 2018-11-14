; WCPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

wcputw proc uses eax ecx edi b:PVOID, l, w
    mov eax,w
    mov ecx,l
    mov edi,b
    .if ah
        rep stosw
    .else
        .repeat
            stosb
            inc edi
        .untilcxz
    .endif
    ret
wcputw endp

    END
