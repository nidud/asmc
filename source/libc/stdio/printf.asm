; PRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

printf proc uses rbx format:LPSTR, argptr:VARARG

    mov ebx,_stbuf( stdout )
    xchg ebx,_output( stdout, format, &argptr )
    _ftbuf( eax, stdout )
    mov eax,ebx
    ret

printf endp

    end
