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

option win64:rsp nosave noauto

.code

_bsrnd proc o:ptr, n:dword

    xor eax,eax
    mov r9d,edx
    shl r9d,6
    .while edx
        sub r9d,64
        mov r8,[rcx+rdx*8-8]
        bsr r8,r8
        .ifnz
            lea eax,[r9d+r8d+1]
            .break
        .endif
        dec edx
    .endw
    ret

_bsrnd endp

    end
