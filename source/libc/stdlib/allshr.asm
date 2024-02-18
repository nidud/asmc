; ALLSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    option dotname

    .code

ifndef _WIN64
_I8RS::
endif

allshr proc watcall q:int64_t, n:int_t
ifdef _WIN64
    mov ecx,edx
    sar rax,cl
else
    mov ecx,ebx
    .if ( cl > 63 )
        sar edx,31
        mov eax,edx
    .elseif ( cl > 31 )
        mov eax,edx
        sar edx,31
        and cl,31
        sar eax,cl
    .else
        shrd eax,edx,cl
        sar edx,cl
    .endif
endif
    ret

allshr endp

ifndef _WIN64
_allshr::
    push    ebx
    mov     ebx,ecx
    call    allshr
    pop     ebx
    ret
endif

    end
