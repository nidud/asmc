; _SUBND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _subnd() - Subtract
;
; The source is subtracted from the destination
; and the result is stored in the destination.
;
; Modifies flags: CF (OF,PF,SF,AF,ZF undefined)
;
include intn.inc

option win64:rsp nosave noauto

.code

_subnd proc a:ptr, b:ptr, n:dword

    xor eax,eax
    .repeat
        mov r9,[rcx]
        shr eax,1
        sbb [rdx],r9
        sbb eax,eax
        add rcx,8
        add rdx,8
        dec r8d
    .untilz
    and eax,3
    shr eax,1
    ret

_subnd endp

    end
