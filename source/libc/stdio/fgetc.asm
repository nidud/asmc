; FGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fgetc proc fp:LPFILE

ifndef _WIN64
    mov ecx,fp
endif
    dec [rcx]._iobuf._cnt
    .ifl

        _filbuf( rcx )
    .else

        inc [rcx]._iobuf._ptr
        mov rax,[rcx]._iobuf._ptr
        movzx eax,byte ptr [rax-1]
    .endif
    ret

fgetc endp

    end
