; _ADDND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _addnd() - Arithmetic Addition
;
; Sums two dword*n sized numbers placing the
; result in the destination.
;
; Modifies flags: CF ZF (OF,PF,SF,AF undefined)
;
include intn.inc

option win64:rsp nosave noauto

.code

_addnd proc a:ptr, b:ptr, n:dword

    xor eax,eax
    .repeat
        mov r9,[rcx]
        shr eax,1
        adc [rdx],r9
        sbb eax,eax
        add rcx,8
        add rdx,8
        dec r8d
    .untilz
    and eax,3
    shr eax,1
    ret

_addnd endp

    end
