; WCSSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcsstr proc s1:LPWSTR, s2:LPWSTR

    xor eax,eax
    .return .if [rdx] == ax

    .while 1

        .for r8w = [rdx] ::

            mov ax,[rcx]
            .return .if !eax

            add rcx,2
            .break .if ax == r8w
        .endf

        lea r9,[rdx+2]
        .for r8 = rcx :: r9 += 2, r8 += 2

            mov ax,[r9]
            .break(1) .if !ax
            .break .if ax != [r8]
        .endf
    .endw
    lea rax,[rcx-2]
    ret

wcsstr endp

    end
