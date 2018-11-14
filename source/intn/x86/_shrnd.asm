; _SHRND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _shrnd() - Shift Right
;
; Shifts the destination right by "count" bits with zeroes shifted
; in on the left.
;
include intn.inc

.code

_shrnd proc uses edi ebx o:ptr, i:dword, n:dword

    mov edx,o
    mov ecx,i
    mov ebx,n
    .if ebx > 1
        .while ecx >= 32
            .for edi=0: edi < ebx: edi++
                mov eax,[edx+edi*4+4]
                mov [edx+edi*4],eax
            .endf
            mov dword ptr [edx+ebx*4-4],0
            sub ecx,32
            dec ebx
        .endw
        mov n,ebx
    .endif
    .if ecx
        .repeat
            mov ebx,n
            xor edi,edi
            .repeat
                mov eax,[edx+ebx*4-4]
                shr edi,1
                rcr eax,1
                sbb edi,edi
                mov [edx+ebx*4-4],eax
            .untilbxz
        .untilcxz
    .endif
    ret

_shrnd endp

    end
