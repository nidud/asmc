; _BSFND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _bsfnd() - Bit Scan Forward
;
; Scans source operand for first bit set. If a bit is found
; set the index to first set bit + 1 is returned.
;
include intn.inc

.code

_bsfnd proc uses esi ebx o:ptr, n:dword

    .for ( esi = o, ecx = n, eax = 0, ebx = 0: ecx: ecx--, ebx += 32, esi += 4 )

        mov edx,[esi]
        bsf edx,edx
        .ifnz
            lea eax,[ebx+edx+1]
            .break
        .endif
    .endf
    ret

_bsfnd endp

    end
