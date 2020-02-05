; UNIXTODOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

    .code

unixtodos proc string:LPSTR

    mov eax,string

    .while 1

        .break .if byte ptr [eax] == 0
        cmp byte ptr [eax],'/'
        lea eax,[eax+1]
        .continue(0) .ifnz
        mov byte ptr [eax-1],'\'
    .endw
    mov eax,string
    ret

unixtodos endp

    END
