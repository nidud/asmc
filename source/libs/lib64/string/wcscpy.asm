; WCSCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcscpy proc dst:wstring_t, src:wstring_t

    mov rax,rcx
    xor ecx,ecx
    .repeat
        mov r8w,[rdx+rcx]
        mov [rax+rcx],r8w
        add ecx,2
    .until !r8w
    ret

wcscpy endp

    end
