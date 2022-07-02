; RAND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .data
     holdrand uint_t 1

    .code

srand proc seed:uint_t

ifndef _WIN64
    mov ecx,seed
endif
    mov holdrand,ecx
    ret

srand endp

rand proc

    mov eax,214013
    mul holdrand
    add eax,2531011
    mov holdrand,eax
    shr eax,16
    and eax,0x7fff
    ret

rand endp

    end
