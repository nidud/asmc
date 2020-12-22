; __MULO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    option win64:rsp noauto

    .code

__mulo proc multiplier:ptr, multiplicand:ptr, highproduct:ptr

    push rcx

    mov rax,[rcx]
    mov r10,[rcx+8]
    mov r9, [rdx+8]

    .if !r10 && !r9
        .if r8
            mov [r8],r9
            mov [r8+8],r9
        .endif
        mul qword ptr [rdx]
    .else
        mov  r11,[rdx]
        mul  r11         ; a * b
        push rax
        xchg rdx,r11
        mov  rax,r10
        mul  rdx         ; a[8] * b
        add  r11,rax
        xchg rcx,rdx
        mov  rax,[rdx]
        mul  r9          ; a * b[8]
        add  r11,rax
        adc  rcx,rdx
        mov  edx,0
        adc  edx,0
        .if r8
            xchg rdx,r9
            mov  rax,r10
            mul  rdx     ; a[8] * b[8]
            add  rax,rcx
            adc  rdx,r9
            mov  [r8],rax
            mov  [r8+8],rdx
        .endif
        pop rax
        mov rdx,r11
    .endif
    pop rcx
    mov [rcx],rax
    mov [rcx+8],rdx
    mov rax,rcx
    ret

__mulo endp

    end
