; _TCSDUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc
include tchar.inc

    .code

_tcsdup proc uses rbx string:LPTSTR

    ldr rax,string
    .if rax

        mov rbx,rax
        .if malloc(&[_tcslen(rax)*TCHAR+TCHAR])

            _tcscpy(rax, rbx)
        .endif
    .endif
    ret

_tcsdup endp

    end
