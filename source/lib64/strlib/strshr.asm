; STRSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strshr(char *string, char ch);
;
; shift string to the right and insert char in front of string
;
include strlib.inc

    .code

    option win64:rsp nosave noauto

strshr proc string:LPSTR, char:UINT

    mov rax,rcx
    mov r8d,[rcx]
    shl r8d,8
    mov r8b,dl

    .while 1

        mov edx,[rcx+3]
        mov [rcx],r8d

        .break .if !(r8d & 0x000000FF)
        .break .if !(r8d & 0x0000FF00)
        .break .if !(r8d & 0x00FF0000)
        .break .if !(r8d & 0xFF000000)

        mov r8d,edx
        add rcx,4
    .endw
    ret

strshr endp

    END
