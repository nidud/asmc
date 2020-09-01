; WCSSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcsstr proc uses esi edi ebx s1:LPWSTR, s2:LPWSTR

    mov edi,s1
    mov esi,s2
    xor eax,eax
    .repeat
        .break .if [esi] == ax
        .while  1
            .for cx = [esi] ::

                mov ax,[edi]
                .break(2) .if !eax
                add edi,2
                .break .if ax == cx
            .endf
            add  esi,2
            .for ebx = edi :: esi += 2, ebx += 2

                mov ax,[esi]
                .break(1) .if !ax
                .break .if ax != [ebx]
            .endf
            mov esi,s2
        .endw
        mov eax,edi
        sub eax,2
    .until 1
    ret

wcsstr endp

    end
