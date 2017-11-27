; _bsfnd() - Bit Scan Forward
;
; Scans source operand for first bit set. If a bit is found
; set the index to first set bit + 1 is returned.
;
include intn.inc

.code

_bsfnd proc uses esi ebx o:ptr, n:dword

    mov esi,o
    mov ecx,n
    xor eax,eax
    xor ebx,ebx
    .while ecx
        mov edx,[esi]
        bsf edx,edx
        .ifnz
            lea eax,[ebx+edx+1]
            .break
        .endif
        dec ecx
        add ebx,32
        add esi,4
    .endw
    ret

_bsfnd endp

    end
