; WCSCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcscpy proc uses rbx dst:wstring_t, src:wstring_t

    ldr rcx,dst
    ldr rdx,src

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
