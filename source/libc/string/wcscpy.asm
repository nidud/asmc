; WCSCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcscpy proc uses rbx dst:wstring_t, src:wstring_t

ifndef _WIN64
    mov ecx,dst
    mov edx,src
endif
    mov rax,rcx
    xor ecx,ecx
    .repeat
        mov bx,[rdx+rcx]
        mov [rax+rcx],bx
        add ecx,2
    .until !bx
    ret

wcscpy endp

    end
