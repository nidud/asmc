; _TSTRRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcsrchr proc string:LPTSTR, chr:int_t

    ldr     rcx,string
    ldr     edx,chr
    sub     rcx,TCHAR
    xor     eax,eax
.0:
    add     rcx,TCHAR
    cmp     TCHAR ptr [rcx],0
    jz      .1
    cmp     _tdl,[rcx]
    jnz     .0
    mov     rax,rcx
    jmp     .0
.1:
    ret

_tcsrchr endp

    end
