; ACRTIOBFUNC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

__acrt_iob_func proc id:dword
ifdef _MSVCRT
    __iob_func()
    imul ecx,id,_iobuf
    add  rax,rcx
else
    ldr ecx,id
    imul eax,ecx,_iobuf
    add  rax,stdin
endif
    ret
    endp

    end
