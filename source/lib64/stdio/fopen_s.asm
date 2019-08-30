; FOPEN_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc

.code

    option win64:nosave

fopen_s proc uses rdi pFile:ptr ptr FILE, filename:ptr sbyte, mode:ptr sbyte

    mov rdi,rcx
    mov rcx,rdx
    mov rdx,r8

    .if !fopen(rcx, rdx)

        _get_errno(0)

    .else

        stosq
        xor eax,eax

    .endif
    ret

fopen_s endp

    end
