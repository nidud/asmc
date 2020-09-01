; PRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

printf proc frame uses rsi rdi rbx format:LPSTR, argptr:VARARG

    lea rsi,stdout
    mov rbx,_stbuf(rsi)
    mov rdi,_output(rsi, format, &argptr)
    _ftbuf(ebx, rsi)
    mov eax,edi
    ret

printf endp

    END
