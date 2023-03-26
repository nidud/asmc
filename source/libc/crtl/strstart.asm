; STRSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strstart proc string:string_t

    mov rax,string
    .repeat

        add rax,1
        .continue(0) .if byte ptr [rax-1] == ' '
        .continue(0) .if byte ptr [rax-1] == 9
    .until 1
    sub rax,1
    ret

strstart endp

    end
