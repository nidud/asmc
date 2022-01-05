; _WCSNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_wcsnicmp proc a:wstring_t, b:wstring_t, count:size_t

    mov eax,1

    .repeat

        .break .if !ax

        xor eax,eax
        .break .if !r8d

        mov ax,[rdx]
        dec r8d
        add rdx,2
        add rcx,2
        .continue(0) .if ax == [rcx-2]

        mov r9w,[rcx-2]
        .if r9w >= 'A' && r9w <= 'Z'
            or r9b,0x20
        .endif
        .if ax >= 'A' && ax <= 'Z'
            or al,0x20
        .endif
        .continue(0) .if r9w == ax

        sbb al,al
        sbb al,-1
    .until 1
    movsx eax,al
    ret

_wcsnicmp endp

    end
