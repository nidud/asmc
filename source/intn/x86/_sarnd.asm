; _SARND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _sarnd() - Shift Arithmetic Right
;
; Shifts the destination right by "count" bits with
; the current sign bit replicated in the leftmost bit.
;
include intn.inc

.code

_sarnd proc uses esi edi ebx o:ptr, i:dword, n:dword

    mov edx,o
    mov ecx,i
    mov ebx,n
    .if ebx > 1
        .while ecx >= 32
            mov esi,[edx+ebx*4-4]
            .for edi=0: edi < ebx: edi++
                mov eax,[edx+edi*4+4]
                mov [edx+edi*4],eax
            .endf
            sar esi,31
            mov [edx+ebx*4-4],esi
            sub ecx,32
            dec ebx
        .endw
        mov n,ebx
    .endif
    .if ecx
        .repeat
            xor edi,edi
            mov esi,[edx+ebx*4-4]
            .repeat
                mov eax,[edx+ebx*4-4]
                shr edi,1
                rcr eax,1
                sbb edi,edi
                mov [edx+ebx*4-4],eax
            .untilbxz
            mov ebx,n
            sar esi,1
            mov [edx+ebx*4-4],esi
        .untilcxz
    .endif
    ret

_sarnd endp

    end
