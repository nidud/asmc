; FPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fprintf proc uses rbx r12 r13 r14 file:ptr FILE, format:string_t, argptr:vararg

    mov r12,rdi
    mov r13,rsi
    mov r14,rax
    mov rbx,_stbuf(rdi)
    mov r14,_output(r12, r13, r14)
    _ftbuf(ebx, r12)
    mov rax,r14
    ret

fprintf endp

    end
