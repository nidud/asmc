; __MULO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    option win64:noauto

    .code

__mulo proc multiplier:ptr, multiplicand:ptr, highproduct:ptr

    mov rax,[rdi]
    mov r10,[rdi+8]
    mov rcx,[rsi+8]

    .if ( !r10 && !rcx )

        .if ( rdx )

            mov [rdx],rcx
            mov [rdx+8],rcx
        .endif
        mul qword ptr [rsi]

    .else
        mov  r8,rdx
        push rdi
        mov  r11,[rsi]
        mul  r11         ; a * b
        push rax
        xchg rdx,r11
        mov  rax,r10
        mul  rdx         ; a[8] * b
        add  r11,rax
        xchg rdi,rdx
        mov  rax,[rdx]
        mul  rcx         ; a * b[8]
        add  r11,rax
        adc  rdi,rdx
        mov  edx,0
        adc  edx,0

        .if ( r8 )

            xchg rdx,rcx
            mov  rax,r10
            mul  rdx     ; a[8] * b[8]
            add  rax,rdi
            adc  rdx,rcx
            mov  [r8],rax
            mov  [r8+8],rdx
        .endif

        pop rax
        mov rdx,r11
        pop rdi
    .endif

    mov [rdi],rax
    mov [rdi+8],rdx
    mov rax,rdi
    ret

__mulo endp

    end
