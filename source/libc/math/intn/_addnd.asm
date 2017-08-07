; _addnd() - Arithmetic Addition
;
; Sums two dword*n sized numbers placing the
; result in the destination.
;
; Modifies flags: CF ZF (OF,PF,SF,AF undefined)
;
include intn.inc

.code

_addnd proc uses esi edi a:ptr, b:ptr, n:dword

    mov edi,a
    mov esi,b
    mov ecx,n
    xor eax,eax
    .repeat
        mov edx,[esi]
        shr eax,1
        adc [edi],edx
        sbb eax,eax
        add esi,4
        add edi,4
    .untilcxz
    and eax,3
    shr eax,1
    ret

_addnd endp

    end
