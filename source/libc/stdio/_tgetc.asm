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
    sub [rcx]._iobuf._cnt,tchar_t
    .ifl
        _tfilbuf(rcx)
    .else
        mov rax,[rcx]._iobuf._ptr
        add [rcx]._iobuf._ptr,tchar_t
        movzx eax,tchar_t ptr [rax]
    .endif
    ret

_gettc endp

    end
