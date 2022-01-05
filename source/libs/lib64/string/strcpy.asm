; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname
    option win64:rsp noauto

strcpy proc dst:string_t, src:string_t

    mov     r9,rcx
    mov     al,[rdx]
    mov     [rcx],al
    test    al,al
    jz      .2

    mov     al,[rdx+1]
    mov     [rcx+1],al
    test    al,al
    jz      .2

    mov     al,[rdx+2]
    mov     [rcx+2],al
    test    al,al
    jz      .2

    mov     al,[rdx+3]
    mov     [rcx+3],al
    test    al,al
    jz      .2

    mov     al,[rdx+4]
    mov     [rcx+4],al
    test    al,al
    jz      .2

    mov     al,[rdx+5]
    mov     [rcx+5],al
    test    al,al
    jz      .2

    mov     al,[rdx+6]
    mov     [rcx+6],al
    test    al,al
    jz      .2

    mov     al,[rdx+7]
    mov     [rcx+7],al
    test    al,al
    jz      .2

    add     rdx,8
    add     rcx,8
    mov     r10,0x8080808080808080
    mov     r11,0x0101010101010101
.0:
    mov     rax,[rdx]
    mov     r8,rax
    sub     r8,r11
    not     rax
    and     r8,rax
    not     rax
    and     r8,r10
    jnz     .1
    mov     [rcx],rax
    add     rcx,8
    add     rdx,8
    jmp     .0
.1:
    mov     [rcx],al
    test    al,al
    jz      .2

    mov     [rcx+1],ah
    test    ah,ah
    jz      .2

    shr     rax,16
    mov     [rcx+2],al
    test    al,al
    jz      .2

    mov     [rcx+3],ah
    test    ah,ah
    jz      .2

    shr     rax,16
    add     rcx,4
    jmp     .1
.2:
    mov     rax,r9
    ret

strcpy endp

    end
