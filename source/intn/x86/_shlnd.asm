; _SHLND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _shlnd() - Shift Left
;
; Shifts the destination left by "count" bits with zeroes shifted
; in on right.
;
include intn.inc

.code

_shlnd proc uses edi ebx o:ptr, i:dword, n:dword

    mov edx,o
    mov ecx,i
    mov ebx,n
    .if ebx > 1
        .while ecx >= 32
            .for edi=ebx: edi: edi--
                mov eax,[edx+edi*4-8]
                mov [edx+edi*4-4],eax
            .endf
            xor eax,eax
            mov [edx],eax
            sub ecx,32
        .endw
    .endif
    .if ecx
        .repeat
            xor ebx,ebx
            xor edi,edi
            .repeat
                mov eax,[edx+ebx*4]
                shr edi,1
                rcl eax,1
                mov [edx+ebx*4],eax
                sbb edi,edi
                add ebx,1
            .until ebx == n
        .untilcxz
    .endif
    ret

_shlnd endp

    end
