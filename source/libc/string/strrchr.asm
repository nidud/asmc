; STRRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strrchr proc string:string_t, chr:int_t

    ldr     rcx,string
    ldr     edx,chr
    dec     rcx
    xor     eax,eax
.0:
    inc     rcx
    cmp     byte ptr [rcx],0
    jz      .2
    cmp     dl,[rcx]
    jnz     .0
    mov     rax,rcx
    jmp     .0
.2:
    ret

strrchr endp

    end
