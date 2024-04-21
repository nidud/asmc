; WCPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

wcputw proc p:PCHAR_INFO, l:int_t, w:uint_t

    ldr eax,w
    ldr rcx,p
    ldr edx,l
    .if eax & 0x00FF0000
        xchg rcx,rdx
        xchg rdx,rdi
        rep  stosd
        mov  rdi,rdx
    .else
        .repeat
            mov [rcx],ax
            add rcx,4
            dec edx
        .until !edx
    .endif
    ret

wcputw endp

    END
