; PRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

printf proc uses rbx r12 r13 format:string_t, argptr:vararg

    mov r12,rax
    mov r13,rdi
    mov rbx,_stbuf(stdout)
    mov r13,_output(stdout, r13, r12)
    _ftbuf(ebx, stdout)
    .return(r13)

printf endp

    END
