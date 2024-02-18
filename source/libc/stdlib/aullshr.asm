; AULLSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    option dotname

    .code

ifndef _WIN64
_U8RS::
endif

aullshr proc watcall q:uint64_t, n:int_t
ifdef _WIN64
    mov ecx,edx
    shr rax,cl
else
    mov ecx,ebx
    .if ( cl > 63 )
        xor eax,eax
        xor edx,edx
    .elseif ( cl > 31 )
        mov eax,edx
        xor edx,edx
        and cl,31
        shr eax,cl
    .else
        shrd eax,edx,cl
        shr edx,cl
    .endif
endif
    ret

aullshr endp

ifndef _WIN64
_aullshr::
__ullshr::
    push    ebx
    mov     ebx,ecx
    call    aullshr
    pop     ebx
    ret
endif

    end
