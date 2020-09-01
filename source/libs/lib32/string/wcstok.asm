; WCSTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
    s0 dd ?

    .code

wcstok proc uses edx ebx s1:LPWSTR, s2:LPWSTR

    mov eax,s1
    .if eax

        mov s0,eax
    .endif

    .for eax=0, ebx=s0: word ptr [ebx]: ebx+=2

        .for ecx=s2, ax=[ecx]: eax, ax != [ebx]: ecx+=2, ax=[ecx]
        .endf

        .break .if !eax
    .endf

    xor eax,eax
    .repeat
        .break .if ax == [ebx]

        .for edx=ebx: word ptr [ebx]: ebx+=2

            .for ecx=s2, ax=[ecx]: eax: ecx+=2, ax=[ecx]

                .if ax == [ebx]

                    mov word ptr [ebx],0
                    add ebx,2

                    .break(1)
                .endif
            .endf
        .endf
        mov eax,edx
    .until 1

    mov s0,ebx
    ret

wcstok endp

    END
