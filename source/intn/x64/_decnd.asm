; _DECND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _decnd() - Decrement
;
; Unsigned binary subtraction of one from the destination.
;
; Modifies flags: CF ZF (OF,PF,SF,AF undefined)
;
include intn.inc

option win64:rsp nosave noauto

.code

_decnd proc a:ptr, n:dword

    sub qword ptr [rcx],1
    sbb eax,eax
    .while edx > 1
        add rcx,8
        shr eax,1
        sbb qword ptr [rcx],0
        sbb eax,eax
        dec edx
    .endw
    and eax,3   ; return carry flag in EAX
    shr eax,1
    ret

_decnd endp

    end
