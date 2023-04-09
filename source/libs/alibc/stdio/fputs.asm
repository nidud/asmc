; FPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc

    .code

fputs proc uses rbx r12 r13 r14 string:LPSTR, fp:LPFILE

    mov rbx,rdi
    mov r14,rsi
    mov r13,_stbuf(r14)
    mov r12,strlen(rbx)
    mov rbx,fwrite(rbx, 1, eax, r14)

    _ftbuf(r13d, r14)
    mov rcx,r14
    xor eax,eax
    .if rbx
	dec rax
    .endif
    ret

fputs endp

    END
