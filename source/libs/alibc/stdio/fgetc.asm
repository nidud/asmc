; FGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fgetc proc fp:LPFILE

    dec [rdi]._iobuf._cnt
    .ifl
        _filbuf(rdi)
    .else
        inc [rdi]._iobuf._ptr
        mov rax,[rdi]._iobuf._ptr
        movzx eax,byte ptr [rax-1]
    .endif
    ret

fgetc endp

    END
