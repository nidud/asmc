; _subnd() - Subtract
;
; The source is subtracted from the destination
; and the result is stored in the destination.
;
; Modifies flags: CF (OF,PF,SF,AF,ZF undefined)
;
include intn.inc

.code

_subnd proc uses esi edi a:ptr, b:ptr, n:dword

    mov edi,a
    mov esi,b
    mov ecx,n
    xor eax,eax
    .repeat
        mov edx,[esi]
        shr eax,1
        sbb [edi],edx
        sbb eax,eax
        add esi,4
        add edi,4
    .untilcxz
    and eax,3
    shr eax,1
    ret

_subnd endp

    end
