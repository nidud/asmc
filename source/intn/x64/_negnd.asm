; _NEGND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _negnd() - Negation
;
include intn.inc

option win64:rsp nosave noauto

.code

_negnd proc p:ptr, n:dword

    neg qword ptr [rcx+rdx*8-8]
    .if edx > 1
        dec edx
        .repeat
            neg qword ptr [rcx+rdx*8-8]
            sbb qword ptr [rcx+rdx*8],0
            dec edx
        .untilz
    .endif
    ret

_negnd endp

    end
