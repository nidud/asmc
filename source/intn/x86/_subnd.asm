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

    .for ( edi=a, esi=b, ecx=n, eax=0: ecx: ecx--, esi+=4, edi+=4 )

        mov edx,[esi]
        shr eax,1
        sbb [edi],edx
        sbb eax,eax
    .endf
    and eax,3
    shr eax,1
    ret

_subnd endp

    end
