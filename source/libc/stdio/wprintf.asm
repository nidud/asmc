; WPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

wprintf proc uses rbx format:LPWSTR, argptr:VARARG

    mov  ebx,_stbuf(stdout)
    xchg rbx,_woutput(stdout, format, &argptr)
    _ftbuf(eax, stdout)
    mov eax,ebx
    ret

wprintf endp

    end
