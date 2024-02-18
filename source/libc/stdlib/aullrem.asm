; AULLREM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    .code

aullrem proc watcall a:uint64_t, b:uint64_t

    call    aulldiv
ifdef _WIN64
    mov     rax,rdx
else
    mov     eax,ebx
    mov     edx,ecx
endif
    ret

aullrem endp

ifndef _WIN64
__ullmod::
_aullrem::
    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    aullrem
    pop     ebx
    ret     16
endif

    end
