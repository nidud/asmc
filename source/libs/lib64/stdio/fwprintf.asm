; FWPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fwprintf proc uses rsi file:LPFILE, format:LPWSTR, argptr:VARARG

    mov  rsi,_stbuf(rcx)
    xchg rsi,_woutput(file, format, &argptr)

    _ftbuf(eax, file)
    mov eax,esi
    ret

fwprintf endp

    END
