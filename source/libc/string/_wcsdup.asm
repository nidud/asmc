; _WCSDUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc

    .code

_wcsdup proc uses rbx string:LPWSTR

    ldr rbx,string
    .if wcslen(rbx)

        .if malloc(&[rax*2+2])

            wcscpy(rax, rbx)
        .endif
    .endif
    ret

_wcsdup endp

    end
