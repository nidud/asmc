; _BSRND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _bsrnd() - Bit Scan Reverse
;
; Scans source operand for first bit set. If a bit is found
; set the index to first set bit + 1 is returned.
;
include intn.inc

.code

_bsrnd proc uses esi ebx o:ptr, n:dword

    .for ( esi = o, ecx = n, eax = 0, ebx = ecx, ebx <<= 5: ecx: ecx-- )

        sub ebx,32
        mov edx,[esi+ecx*4-4]
        bsr edx,edx
        .ifnz
            lea eax,[ebx+edx+1]
            .break
        .endif
    .endf
    ret

_bsrnd endp

    end
