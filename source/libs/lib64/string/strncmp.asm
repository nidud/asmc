; STRNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

strncmp proc a:string_t, b:string_t, count:size_t

    .repeat

        xor eax,eax
        .break .if !r8
        .while 1
            mov al,[rcx]
            cmp al,[rdx]
            lea rdx,[rdx+1]
            lea rcx,[rcx+1]
            .break .ifnz
            .break(1) .if !al
            dec r8
            .continue(0) .ifnz
            xor eax,eax
            .break(1)
        .endw
        sbb al,al
        sbb al,-1
        movsx rax,al
    .until 1
    ret

strncmp endp

    end
