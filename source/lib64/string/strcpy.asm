; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strcpy::

    mov r9,rcx
    mov al,[rdx]
    mov [rcx],al
    .repeat
        .break .if !al
        mov al,[rdx+1]
        mov [rcx+1],al
        .break .if !al
        mov al,[rdx+2]
        mov [rcx+2],al
        .break .if !al
        mov al,[rdx+3]
        mov [rcx+3],al
        .break .if !al
        mov al,[rdx+4]
        mov [rcx+4],al
        .break .if !al
        mov al,[rdx+5]
        mov [rcx+5],al
        .break .if !al
        mov al,[rdx+6]
        mov [rcx+6],al
        .break .if !al
        mov al,[rdx+7]
        mov [rcx+7],al
        .break .if !al
        lea rdx,[rdx+8]
        lea rcx,[rcx+8]
        mov r10,0x8080808080808080
        mov r11,0x0101010101010101
        .while 1
            mov rax,[rdx]
            mov r8,rax
            sub r8,r11
            not rax
            and r8,rax
            not rax
            and r8,r10
            .break .ifnz
            mov [rcx],rax
            add rcx,8
            add rdx,8
        .endw
        .while 1
            mov [rcx],al
            .break .if !al
            mov [rcx+1],ah
            .break .if !ah
            shr rax,16
            mov [rcx+2],al
            .break .if !al
            mov [rcx+3],ah
            .break .if !ah
            shr rax,16
            add rcx,4
        .endw
    .until 1
    mov rax,r9
    ret

    END
