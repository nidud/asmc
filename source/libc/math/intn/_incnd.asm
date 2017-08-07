; _incnd() - Increment
;
; Adds one to destination unsigned binary operand.
;
; Modifies flags: CF ZF (OF,PF,SF,AF undefined)
;
include intn.inc

.code

_incnd proc a:ptr, n:dword

    mov edx,a
    mov ecx,n
    add dword ptr [edx],1
    sbb eax,eax
    .while ecx > 1
        add edx,4
        shr eax,1
        adc dword ptr [edx],0
        sbb eax,eax
        dec ecx
    .endw
    and eax,3   ; return carry flag in EAX
    shr eax,1
    ret

_incnd endp

    end
