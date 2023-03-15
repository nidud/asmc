; __ACRT_IOB_FUNC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

__acrt_iob_func proc id:dword

ifndef _WIN64
    mov ecx,id
endif
    imul eax,ecx,_iobuf
    add  rax,stdin
    ret

__acrt_iob_func endp

    end
