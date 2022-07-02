; ISPRINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isprint proc c:int_t

ifndef _WIN64
    mov ecx,c
endif
    mov eax,1
    .if ( cl < 0x20 || cl >= 0x7F )

        xor eax,eax
    .endif
    ret

isprint endp

    end

