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

.code

_decnd proc a:ptr, n:dword

    mov edx,a
    mov ecx,n
    sub dword ptr [edx],1
    sbb eax,eax
    .while ecx > 1
        add edx,4
        shr eax,1
        sbb dword ptr [edx],0
        sbb eax,eax
        dec ecx
    .endw
    and eax,3   ; return carry flag in EAX
    shr eax,1
    ret

_decnd endp

    end
