; VFWPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

vfwprintf proc uses esi file:LPFILE, format:LPWSTR, args:PVOID

    mov esi,_stbuf(file)
    xchg esi,_woutput(file, format, args)
    _ftbuf(eax, file)
    mov eax,esi
    ret

vfwprintf endp

    END
