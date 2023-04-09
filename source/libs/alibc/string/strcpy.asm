; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strcpy proc dst:string_t, src:string_t

    mov     r9,rdi
    mov     al,[rsi]
    mov     [rdi],al
    test    al,al
    jz      .2

    mov     al,[rsi+1]
    mov     [rdi+1],al
    test    al,al
    jz      .2

    mov     al,[rsi+2]
    mov     [rdi+2],al
    test    al,al
    jz      .2

    mov     al,[rsi+3]
    mov     [rdi+3],al
    test    al,al
    jz      .2

    mov     al,[rsi+4]
    mov     [rdi+4],al
    test    al,al
    jz      .2

    mov     al,[rsi+5]
    mov     [rdi+5],al
    test    al,al
    jz      .2

    mov     al,[rsi+6]
    mov     [rdi+6],al
    test    al,al
    jz      .2

    mov     al,[rsi+7]
    mov     [rdi+7],al
    test    al,al
    jz      .2

    add     rsi,8
    add     rdi,8
    mov     r10,0x8080808080808080
    mov     r11,0x0101010101010101
.0:
    mov     rax,[rsi]
    mov     r8,rax
    sub     r8,r11
    not     rax
    and     r8,rax
    not     rax
    and     r8,r10
    jnz     .1
    mov     [rdi],rax
    add     rdi,8
    add     rsi,8
    jmp     .0
.1:
    mov     [rdi],al
    test    al,al
    jz      .2

    mov     [rdi+1],ah
    test    ah,ah
    jz      .2

    shr     rax,16
    mov     [rdi+2],al
    test    al,al
    jz      .2

    mov     [rdi+3],ah
    test    ah,ah
    jz      .2

    shr     rax,16
    add     rdi,4
    jmp     .1
.2:
    mov     rax,r9
    ret

strcpy endp

    end
