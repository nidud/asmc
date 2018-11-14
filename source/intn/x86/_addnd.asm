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

.code

_addnd proc uses esi edi a:ptr, b:ptr, n:dword

    .for ( edi = a, esi = b, ecx = n, eax = 0: ecx: ecx--, esi += 4, edi += 4 )

        mov edx,[esi]
        shr eax,1
        adc [edi],edx
        sbb eax,eax
    .endf
    and eax,3
    shr eax,1
    ret

_addnd endp

    end
