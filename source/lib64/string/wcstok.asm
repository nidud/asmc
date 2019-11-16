; WCSTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
    s0 LPWSTR ?

    .code

    option win64:rsp noauto nosave

wcstok proc s1:LPWSTR, s2:LPWSTR

    mov rax,rcx
    .if rax

        mov s0,rax
    .endif

    .for eax = 0, r8 = s0 : word ptr [r8]: r8 += 2

        .for rcx = rdx, ax = [rcx] : ax && ax != [r8] : rcx += 2, ax = [rcx]
        .endf

        .break .if !rax
    .endf

    xor eax,eax
    .repeat

        .break .if ax == [r8]

        .for rcx = r8 : word ptr [r8] : r8 += 2

            .for ax = [rdx] : eax : rdx += 2, ax = [rdx]

                .if ax == [r8]

                    mov word ptr [r8],0
                    add r8,2

                    .break(1)
                .endif
            .endf
        .endf
        mov rax,rcx
    .until 1

    mov s0,r8
    ret

wcstok endp

    END
