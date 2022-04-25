; PRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

printf proc uses rbx r12 r13 r14 format:string_t, argptr:vararg

    mov r14,rax
    mov r13,rdi
    lea r12,stdout
    mov rbx,_stbuf(r12)
    mov r13,_output(r12, r13, r14)
    _ftbuf(ebx, r12)
    .return(r13)

printf endp

    END
