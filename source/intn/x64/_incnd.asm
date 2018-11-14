; _INCND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _incnd() - Increment
;
; Adds one to destination unsigned binary operand.
;
; Modifies flags: CF ZF (OF,PF,SF,AF undefined)
;
include intn.inc

option win64:rsp nosave noauto

.code

_incnd proc a:ptr, n:dword

    add qword ptr [rcx],1
    sbb eax,eax
    .while edx > 1
        add rcx,8
        shr eax,1
        adc qword ptr [rcx],0
        sbb eax,eax
        dec edx
    .endw
    and eax,3   ; return carry flag in EAX
    shr eax,1
    ret

_incnd endp

    end
