; _TGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_gettc proc fp:ptr FILE

    ldr rcx,fp
    sub [rcx]._iobuf._cnt,TCHAR
    .ifl
        _tfilbuf(rcx)
    .else
        mov rax,[rcx]._iobuf._ptr
        add [rcx]._iobuf._ptr,TCHAR
        movzx eax,TCHAR ptr [rax]
    .endif
    ret

_gettc endp

    end
