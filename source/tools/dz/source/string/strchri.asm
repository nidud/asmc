; STRCHRI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

    .code

    option stackbase:esp

strchri PROC uses esi string:LPSTR, char:SIZE_T

    mov esi,string
    movzx eax,byte ptr char

    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb cl,cl
    and cl,'a'-'A'
    add cl,al
    add cl,'A'

    .repeat

        mov al,[esi]
        .return .if !eax

        add esi,1
        sub al,'A'
        cmp al,'Z'-'A'+1
        sbb ch,ch
        and ch,'a'-'A'
        add al,ch
        add al,'A'

    .until al != cl

    mov eax,esi
    dec eax
    ret

strchri ENDP

    END
