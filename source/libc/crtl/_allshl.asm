; _ALLSHL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef _WIN64
    .386
    .model flat, c
endif
    .code

    option dotname

ifdef _WIN64

    int 3

else

_U8LS::             ; Watcom
_I8LS::

    mov ecx,ebx     ; edx:eax << bl

_allshl::           ; edx:eax << cl
__llshl::           ; Microsoft

    .if ( cl < 64 )

        .if ( cl < 32 )

            shld edx,eax,cl
            shl eax,cl
            ret
        .endif

        and ecx,31
        mov edx,eax
        xor eax,eax
        shl edx,cl
        ret
    .endif

    xor eax,eax
    xor edx,edx
    ret

endif

    end
