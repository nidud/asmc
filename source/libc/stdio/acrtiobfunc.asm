; ACRTIOBFUNC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

__acrt_iob_func proc id:dword

    ldr ecx,id
    imul eax,ecx,_iobuf
    add  rax,stdin
    ret

__acrt_iob_func endp

    end
