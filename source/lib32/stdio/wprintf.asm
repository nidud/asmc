; WPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

wprintf proc c uses esi format:LPWSTR, argptr:VARARG

    mov  esi,_stbuf(&stdout)
    xchg esi,_woutput(&stdout, format, &argptr)
    mov  edx,eax

    _ftbuf(edx, &stdout)
    mov eax,esi
    ret

wprintf endp

    END
