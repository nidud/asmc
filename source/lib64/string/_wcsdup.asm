; _WCSDUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc

    .code

_wcsdup proc frame string:LPWSTR

    .if wcslen(rcx)

        add eax,2
        .if malloc(rax)

            wcscpy(rax, string)
        .endif
    .endif
    ret

_wcsdup endp

    end
