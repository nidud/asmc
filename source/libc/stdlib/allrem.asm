; ALLREM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    .code

allrem proc watcall a:int64_t, b:int64_t

    call    alldiv
ifdef _WIN64
    mov     rax,rdx
else
    mov     eax,ebx
    mov     edx,ecx
endif
    ret

allrem endp

ifndef _WIN64
_allrem::
    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    allrem
    pop     ebx
    ret     16
endif

    end
