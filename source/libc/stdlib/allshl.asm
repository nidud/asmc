; ALLSHL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    option dotname

    .code

ifndef _WIN64
_U8LS::
_I8LS::
endif

allshl proc watcall q:int64_t, n:int_t
ifdef _WIN64
    mov ecx,edx
    shl rax,cl
else
    mov ecx,ebx
    .if ( cl < 64 )

        .if ( cl < 32 )
            shld edx,eax,cl
            shl eax,cl
        .else
            and ecx,31
            mov edx,eax
            xor eax,eax
            shl edx,cl
        .endif
    .else
        xor eax,eax
        xor edx,edx
    .endif
endif
    ret

allshl endp

ifndef _WIN64
_allshl::
__llshl::
    push    ebx
    mov     ebx,ecx
    call    allshl
    pop     ebx
    ret
endif

    end
