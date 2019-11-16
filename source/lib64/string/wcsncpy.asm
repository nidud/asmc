; WCSNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcsncpy proc s1:LPWSTR, s2:LPWSTR, count:SIZE_T

    mov r9,rcx
    .for ( eax = 0: r8 : rcx += 2, rdx += 2, r8-- )

        mov ax,[rdx]
        mov [rcx],ax
        .break .if !eax
    .endf

    mov word ptr [rcx-2],0
    mov rax,r9
    ret

wcsncpy endp

    END
