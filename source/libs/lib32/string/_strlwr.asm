; _STRLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_strlwr proc uses esi string:LPSTR

    mov esi,string

    .while 1

        mov al,[esi]
        .break .if !al
        sub al,'A'
        cmp al,'Z' - 'A' + 1
        sbb al,al
        and al,'a' - 'A'
        xor [esi],al
        inc esi
    .endw
    mov eax,string
    ret

_strlwr endp

    END
