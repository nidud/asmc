; FWPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fwprintf proc c uses esi file:LPFILE, format:LPWSTR, argptr:VARARG

    mov  esi,_stbuf(file)
    xchg esi,_woutput(file, format, &argptr)

    _ftbuf(eax, file)
    mov eax,esi
    ret

fwprintf endp

    END
