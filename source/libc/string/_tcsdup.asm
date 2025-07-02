; _TCSDUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc
include tchar.inc

    .code

_tcsdup proc uses rbx string:tstring_t

    ldr rax,string
    .if rax

        mov rbx,rax
        .if malloc(&[_tcslen(rax)*tchar_t+tchar_t])

            _tcscpy(rax, rbx)
        .endif
    .endif
    ret

_tcsdup endp

    end
