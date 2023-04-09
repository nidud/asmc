; _INITTERM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

externdef __ImageBase:size_t

    .code

_initterm proc uses rbx r12 pfbegin:ptr, pfend:ptr

    mov rbx,rdi
    mov r12,rsi
    ;
    ; walk the table of function pointers from the bottom up, until
    ; the end is encountered.  Do not skip the first entry.  The initial
    ; value of pfbegin points to the first valid entry.  Do not try to
    ; execute what pfend points to.  Only entries before pfend are valid.
    ;
    sub r12,rbx
    shr r12,3
    .ifnz

        .for ( : r12 : r12--, rbx+=8 )

            mov rax,[rbx]
            .break .if !rax

            add  rax,__ImageBase
            call rax
        .endf
    .endif
    ret

_initterm endp

    end
