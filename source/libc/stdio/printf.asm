; PRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

printf proc uses rdi rbx format:LPSTR, argptr:VARARG

    mov ebx,_stbuf( stdout )
    mov edi,_output( stdout, format, &argptr )
    _ftbuf( ebx, stdout )
    mov eax,edi
    ret

printf endp

    end
