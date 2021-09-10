; _WCSDUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc

    .code

_wcsdup proc string:LPWSTR

    .if wcslen(rcx)

        .if malloc(&[rax*2+2])

            wcscpy(rax, string)
        .endif
    .endif
    ret

_wcsdup endp

    end
