; STREOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

    .code

    option stackbase:esp

streol proc uses ebx edx string:LPSTR

    mov eax,string

    .repeat

        mov edx,[eax]
        add eax,4
        lea ecx,[edx-0x01010101]
        not edx
        and ecx,edx
        and ecx,0x80808080
        xor edx,not 0x0A0A0A0A
        lea ebx,[edx-0x01010101]
        not edx
        and ebx,edx
        and ebx,0x80808080
        or  ecx,ebx

    .untilnz

    bsf ecx,ecx
    shr ecx,3
    lea eax,[eax+ecx-4]

    .return .if eax == string
    .return .if BYTE PTR [eax] == 0
    .return .if BYTE PTR [eax-1] != 0x0D

    dec eax
    ret

streol endp

    end
