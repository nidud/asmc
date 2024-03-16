; _TWSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include wsub.inc
include malloc.inc

    .code

    assume rbx:PWSUB

_twsopen proc uses rbx wp:PWSUB

    ldr rbx,wp

    xor eax,eax
    mov [rbx].flags,eax
    mov [rbx].count,eax
    mov [rbx].mask,rax
    mov [rbx].fcb,rax
    mov [rbx].path,malloc(WMAXPATH*TCHAR)
    .if ( rax )
        mov rax,rbx
    .endif
    ret

_twsopen endp

    end
