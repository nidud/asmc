; ALLSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    option dotname

    .code

ifndef _WIN64
_allshr::
endif

allshr proc asmcall q:int64_t, n:int_t
ifdef _WIN64
    mov ecx,edx
    sar rax,cl
else
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
    endp

ifndef _WIN64
_I8RS::
    mov     ecx,ebx
    call    allshr
    ret
endif

    end
