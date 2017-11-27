; _bsfnd() - Bit Scan Forward
;
; Scans source operand for first bit set. If a bit is found
; set the index to first set bit + 1 is returned.
;
include intn.inc

option win64:rsp nosave noauto

.code

_bsfnd proc o:ptr, n:dword

    xor eax,eax
    xor r9d,r9d
    .while edx
        mov r8,[rcx]
        bsf r8,r8
        .ifnz
            lea eax,[r9d+r8d+1]
            .break
        .endif
        dec edx
        add r9d,64
        add rcx,8
    .endw
    ret

_bsfnd endp

    end
